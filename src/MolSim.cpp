
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
    LOG4CXX_INFO(molsimLogger, "Hi from MolSim. Starting code execution...");

    switch (argc) {
        case 2:
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
    if(isPT) startPT();

    std::unique_ptr<molsimInput> ptr (input(xmlFile));

    auto sim = Simulation(*ptr);
    sim.start(isPT);

    if(isPT) endPT();
    LOG4CXX_INFO(molsimLogger, "output written. Terminating...");
    return 0;
}

void startPT(){
    LOG4CXX_INFO(molsimLogger, "Starting performance test.");
    auto offptr =  Level::getOff();
    molsimFileLogger->setLevel(offptr);
    molsimLogger->setLevel(offptr);
    log4cxx::Logger::getLogger("particle")->setLevel(offptr);
    log4cxx::Logger::getLogger("filereader")->setLevel(offptr);
    log4cxx::Logger::getLogger("vtkWriter")->setLevel(offptr);
    ptStartTime = std::chrono::high_resolution_clock::now().time_since_epoch();
}

void endPT(){
    auto ptEndTime = std::chrono::high_resolution_clock::now().time_since_epoch();
    ptEndTime -= ptStartTime;
    std::cout<<"Performance test ended. Elapsed time: "<< ptEndTime.count() << " ns";
}

void help() {
    std::string help = "This Program should be called as follows:\n"
    "./MolSim t_end delta_t {-f filename | -c cuboid_number <cuboid_data>...}\n"
    "---------------------------------------------------------------\n"
    "t_end:\t\t\tend time of the simulation\n"
    "delta_t:\t\tlength of time step between iterations\n"
    "-f, --file:\t\tenables input via file. Accepted file extensions are .particles and .cuboids.\n"
    "\t\t\t\tThe corresponding file formats are specified in the project's ReadMe.\n"
    "-c, --cuboid:\tallows for direct input of cuboid parameters. " //no newline
    "The data is expected to be given in the following order:\n"
    "\t\t\t\t\t<position of cuboid> - 3 double values\n"
    "\t\t\t\t\t<number of particles per dimension> - 3 integer values\n"
    "\t\t\t\t\t<mesh width> - 1 double value\n"
    "\t\t\t\t\t<mass of 1 particle> - 1 double value\n"
    "\t\t\t\t\t<initial velocity> - 3 double values\n"
    "\t\t\t\tdivided by blank spaces and in a single line.\n"
    "\t\t\t\tData of multiple cuboids must also be given in a single line with a blank space in between.\n"
    "This help text can be printed using ./MolSim -h or ./MolSim --help.\n";
    LOG4CXX_INFO(molsimLogger, help);
}