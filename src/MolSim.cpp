
#include "Simulation.h"
#include "xml/molsimInput.cxx"
#include <chrono>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <iostream>

using namespace log4cxx;
using namespace log4cxx::helpers;


/**
 * Output help text for calling the program.
 */
void help();

/**
 * Execute main routine with xml input
 * @param argsv
 * @return
 */
int xmlRoutine(char * xmlFile, bool isPT = false);

/**
 * Start performance test timer.
 */
void startPT();

/**
 * End performance test timer.
 */
void endPT();

//static logger variables molsimLogger
log4cxx::LoggerPtr molsimLogger(log4cxx::Logger::getLogger("molsim.console"));
log4cxx::LoggerPtr molsimFileLogger(log4cxx::Logger::getLogger("molsim"));

std::chrono::duration<int64_t, std::nano> ptStartTime;

/**
 * Main function.
 * @param argc
 * @param argsv
 * @return
 */
int main(int argc, char *argsv[]) {
    PropertyConfigurator::configure("../log4cxx.cfg");
    LOG4CXX_INFO(molsimLogger, "Hi from MolSim. Starting code execution. This may take a while...");

    switch (argc) {
        case 2:
            if (!strcmp(argsv[1], "-h") || !strcmp(argsv[1], "-help")) {
                help();
                return 0;
            }
            return xmlRoutine(argsv[1]);
        case 3:
            if(!strcmp(argsv[2], "-pt")){
                return xmlRoutine(argsv[1], true);
            }
        default:
            LOG4CXX_FATAL(molsimLogger, "Erroneous program call!");
            help();
            return -1;
    }
}

int xmlRoutine(char * xmlFile, bool isPT) {
    //LOG4CXX_DEBUG(molsimLogger, "Reading EndTime:\t"<<xmlReader.getEndTime());
    if (isPT) startPT();
    std::unique_ptr<molsimInput> inputFile;
    try {
        inputFile = input(xmlFile);
    } catch (const xml_schema::exception& e) {
        LOG4CXX_FATAL(molsimLogger, e.what() << "\nError details: " << e);
        help();
        return -1;
    }
    //std::unique_ptr<molsimInput> ptr(input(xmlFile));

    auto sim = Simulation(*inputFile);
    sim.start(isPT);

    if(isPT) endPT();
    LOG4CXX_INFO(molsimLogger, "output written. Terminating...");
    return 0;
}

void startPT(){
    LOG4CXX_INFO(molsimLogger, "Starting performance test.");
    auto offptr =  Level::getOff();
    molsimFileLogger->setLevel(offptr);
    //molsimLogger->setLevel(offptr); //can be activated because it's only called when there is a FATAL error
    log4cxx::Logger::getLogger("particle")->setLevel(offptr);
    log4cxx::Logger::getLogger("filereader")->setLevel(offptr);
    log4cxx::Logger::getLogger("vtkWriter")->setLevel(offptr);
    log4cxx::Logger::getLogger("linkedcellcont")->setLevel(offptr);
    ptStartTime = std::chrono::high_resolution_clock::now().time_since_epoch();
}

void endPT(){
    auto ptEndTime = std::chrono::high_resolution_clock::now().time_since_epoch();
    ptEndTime -= ptStartTime;
    LOG4CXX_INFO(molsimLogger, "Performance test ended. Elapsed time: "<< ptEndTime.count() << " ns");
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
    LOG4CXX_INFO(molsimLogger, help);
}