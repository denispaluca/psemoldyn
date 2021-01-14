
#include "Simulation.h"
#include <chrono>
#include <iostream>
#include <fstream>

#ifdef WITH_LOG4CXX
    #include <log4cxx/logger.h>
    #include <log4cxx/propertyconfigurator.h>
    using namespace log4cxx;
    using namespace log4cxx::helpers;
#endif

/**
 * Output help text for calling the program.
 */
void help();

/**
 * Execute main routine with xml input
 * @param argsv
 * @return
 */
int xmlRoutine(std::string xmlFile, bool isPT = false);

/**
 * Start performance test for complete MolSim
 */
void startPTMolSim();

/**
 * Start performance test timer.
 */
void startPT();

/**
 * End performance test timer.
 */
void endPT(int, int);

#ifdef WITH_LOG4CXX
//static logger variables molsimLogger
log4cxx::LoggerPtr molsimLogger(log4cxx::Logger::getLogger("molsim.console"));
log4cxx::LoggerPtr molsimFileLogger(log4cxx::Logger::getLogger("molsim"));
#endif


std::chrono::duration<int64_t, std::nano> ptStartTime;
std::chrono::duration<int64_t, std::nano> ptStartMolSim;

/**
 * Main function.
 * @param argc
 * @param argsv
 * @return
 */
int main(int argc, char *argsv[]) {
#ifdef WITH_LOG4CXX
    PropertyConfigurator::configure("../log4cxx.cfg");
    LOG4CXX_INFO(molsimLogger, "Hi from MolSim. Starting code execution. This may take a while...");
#endif

    switch (argc) {
        case 2:
            if (!strcmp(argsv[1], "-h") || !strcmp(argsv[1], "-help")) {
                help();
                return 0;
            }
            return xmlRoutine(argsv[1]);
        case 3:
            if(!strcmp(argsv[2], "-pt")){
                startPTMolSim();
                return xmlRoutine(argsv[1], true);
            }
        default:
#ifdef WITH_LOG4CXX
            LOG4CXX_FATAL(molsimLogger, "Erroneous program call!");
#endif

            help();
            return -1;
    }
}

int xmlRoutine(std::string xmlFile, bool isPT) {
    //LOG4CXX_DEBUG(molsimLogger, "Reading EndTime:\t"<<xmlReader.getEndTime());

    std::unique_ptr<molsimInput> inputFile;
    try {
        inputFile = input(xmlFile);
    } catch (const xml_schema::exception& e) {
#ifdef WITH_LOG4CXX
        LOG4CXX_FATAL(molsimLogger, e.what() << "\nError details: " << e);
#endif
        help();
        return -1;
    }

    auto sim = Simulation(*inputFile);
    int molecules = sim.getNumParticles();
    if (isPT) startPT();
    int iterations = sim.start(isPT);

    if(isPT) endPT(molecules, iterations);

    if(inputFile->checkpoint()){
        xml_schema::namespace_infomap map;
        map[""].name = "";
        map[""].schema = "../src/xml/molsimInput.xsd";
        size_t lastindex = xmlFile.find_last_of('.');
        auto rawname = xmlFile.substr(0, lastindex);
        std::ofstream ofs (rawname + "_checkpoint.xml");
        input(ofs, sim.checkpoint(), map);
    }
#ifdef WITH_LOG4CXX
    LOG4CXX_INFO(molsimLogger, "output written. Terminating...");
#endif

    return 0;
}
void startPTMolSim(){
    ptStartMolSim = std::chrono::high_resolution_clock::now().time_since_epoch();
}

void startPT(){
#ifdef WITH_LOG4CXX
    LOG4CXX_INFO(molsimLogger, "Starting performance test.");
    auto offptr =  Level::getOff();
    molsimFileLogger->setLevel(offptr);
    //molsimLogger->setLevel(offptr); //can be activated because it's only called when there is a FATAL error
    log4cxx::Logger::getLogger("particle")->setLevel(offptr);
    log4cxx::Logger::getLogger("filereader")->setLevel(offptr);
    log4cxx::Logger::getLogger("vtkWriter")->setLevel(offptr);
    log4cxx::Logger::getLogger("linkedcellcont")->setLevel(offptr);
#else
    std::cout << "Starting performance test.\n";
#endif

    ptStartTime = std::chrono::high_resolution_clock::now().time_since_epoch();
}

void endPT(int numParticles, int iterations){
    auto ptEndTime = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto ptMolSim = std::chrono::high_resolution_clock::now().time_since_epoch();
    ptMolSim -= ptStartMolSim;
    ptEndTime -= ptStartTime;
    double mups = ((long) numParticles * (long) iterations * 1000000000) / (double) ptEndTime.count();

#ifdef WITH_LOG4CXX
    LOG4CXX_INFO(molsimLogger, "Performance test ended."
        << "\n\tTotal elapsed time:          " << ptMolSim.count() << "ns (" << ((double) ptMolSim.count())/1000000000 << "s)"
        << "\n\tElapsed time main loop:      " << ptEndTime.count() << "ns (" << ((double) ptEndTime.count())/1000000000 << "s)"
        << "\n\t#Particles:                  " << numParticles
        << "\n\tIterations:                  " << iterations
        << "\n\t#Particles * Iterations:     " << numParticles * iterations
        << "\n\tMolecule-updates per second: " << mups << "MUPS/s (" << mups/1000000 << "MMPUS/s)");
#else
    std::cout << "Performance test ended."
        << "\n\tTotal elapsed time:          " << ptMolSim.count() << "ns (" << ((double) ptMolSim.count())/1000000000 << "s)"
        << "\n\tElapsed time main loop:      " << ptEndTime.count() << "ns (" << ((double) ptEndTime.count())/1000000000 << "s)"
        << "\n\t#Particles:                  " << numParticles
        << "\n\tIterations:                  " << iterations
        << "\n\t#Particles * Iterations:     " << numParticles * iterations
        << "\n\tMolecule-updates per second: " << mups << "MUPS/s (" << mups/1000000 << "MMPUS/s)" << std::endl;
#endif
}

void help() {
    std::string help = "This program should be called as follows:\n"
                       "./MolSim xmlInputFile {-pt}\n"
                       "-----------------------------------------\n"
                       "\txmlInputFile\tpath to the xmlInputFile with scheme molsimInput.xsd\n"
                       "\t\t\t\t\tSee molsimInput.xsd for the XML Schema Definition\n"
                       "\t-pt\t\t\t\tRun performance test\n"
                       "-----------------------------------------\n"
                       "This help text can be printed using ./MolSim -h or ./MolSim -help.";
#ifdef WITH_LOG4CXX
    LOG4CXX_INFO(molsimLogger, help);
#else
    std::cout << help << std::endl;
#endif

}