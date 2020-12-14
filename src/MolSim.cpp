
#include "Simulation.h"
#include "xml/molsimInput.cxx"
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

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
int xmlRoutine(char * xmlFile);


//static logger variables molsimLogger
log4cxx::LoggerPtr molsimLogger(log4cxx::Logger::getLogger("molsim.console"));
log4cxx::LoggerPtr molsimFileLogger(log4cxx::Logger::getLogger("molsim"));

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
        default:
            LOG4CXX_FATAL(molsimLogger, "Erroneous program call!");
            help();
            return -1;
    }
}

int xmlRoutine(char * xmlFile) {
    //LOG4CXX_DEBUG(molsimLogger, "Reading EndTime:\t"<<xmlReader.getEndTime());
    std::unique_ptr<molsimInput> ptr (input(xmlFile));

    auto sim = Simulation(*ptr);
    sim.start();

    return 0;
}

void help() {
    std::string help = "";
    help +=       "./MolSim t_end delta_t {-f filename | -c cuboid_number <cuboid_data>...}\n";
    help +=       "---------------------------------------------------------------\n";
    help +=       "t_end:\t\t\tend time of the simulation\n";
    help +=       "delta_t:\t\tlength of time step between iterations\n";
    help +=       "-f, --file:\t\tenables input via file. Accepted file extensions are .particles and .cuboids.\n";
    help +=       "\t\t\t\tThe corresponding file formats are specified in the project's ReadMe.\n";
    help +=       "-c, --cuboid:\tallows for direct input of cuboid parameters. The data is expected to be given in the following order:\n";
    help +=       "\t\t\t\t\t<position of cuboid> - 3 double values\n";
    help +=       "\t\t\t\t\t<number of particles per dimension> - 3 integer values\n";
    help +=       "\t\t\t\t\t<mesh width> - 1 double value\n";
    help +=       "\t\t\t\t\t<mass of 1 particle> - 1 double value\n";
    help +=       "\t\t\t\t\t<initial velocity> - 3 double values\n";
    help +=       "\t\t\t\tdivided by blank spaces and in a single line.\n";
    help +=       "\t\t\t\tData of multiple cuboids must also be given in a single line with a blank space in between.\n";
    help +=       "This help text can be printed using ./MolSim -h or ./MolSim --help.\n";
    LOG4CXX_INFO(molsimLogger, "This Program should be called as follows:\n" << help);
}