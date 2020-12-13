
#include "FileReader.h"
#include "utils/ArrayUtils.h"
#include "utils/ForceUtils.h"

#include <iostream>
#include <regex>
#include <outputWriter/VTKWriter.h>
#include "ParticleContainer.h"
#include "ParticleGenerator.h"

/*
 * Log4cxx includes
 */
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

/**
 * XML Input
 */
#include "xml/molsimInput.cxx"

using namespace log4cxx;
using namespace log4cxx::helpers;

using namespace std;

/**
 * Plot the particles to a vtu-file.
 * @param iteration Iteration counter
 * @param particles Vector of particles to be plotted
 * @return
 */
void plotParticles(int iteration, std::vector<Particle> &particles);

/**
 * Output help text for calling the program.
 */
void help();

/**
 * Execute main molsim Routine
 * @param argc
 * @param argsv
 * @return
 */
int mainRoutine(int argc, char *argsv[]);

/**
 * Execute main routine with xml input
 * @param argsv
 * @return
 */
int xmlRoutine(char *argsv[]);

constexpr double start_time = 0;
double t_end = 0.0;
double delta_t = 0.0;

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
        case 3:
            if (!strcmp(argsv[1], "-xml")) {
                return xmlRoutine(argsv);
            }
        case 4:
        case 2:
            if (!strcmp(argsv[1], "-h") || !strcmp(argsv[1], "-help")) {
                help();
                return 0;
            }
        case 1:
            LOG4CXX_FATAL(molsimLogger, "Erroneous program call!");
            help();
            return -1;
        default:
            return mainRoutine(argc, argsv);
    }
}

int xmlRoutine(char *argsv[]) {
    fileReader(argsv[1]);
    //LOG4CXX_DEBUG(molsimLogger, "Reading EndTime:\t"<<xmlReader.getEndTime());
    return 0;
}

int mainRoutine(int argc, char *argsv[]) {
  double current_time = start_time;
  t_end = std::stod(argsv[1]);
  delta_t = std::stod(argsv[2]);

  ParticleContainer particleContainer = ParticleContainer();
  ParticleGenerator particleGenerator = ParticleGenerator();

  std::string input_method = argsv[3];
  if(input_method == "-f" || input_method == "--file"){
      if (std::regex_match(argsv[4], std::regex(".+\\.particles"))) {
          particleContainer = ParticleContainer(argsv[4]);
      } else if (std::regex_match(argsv[4], std::regex(".+\\.cuboids"))) {
          particleGenerator = ParticleGenerator(argsv[4]);
          particleContainer = particleGenerator.getParticles();
      } else {
          LOG4CXX_FATAL(molsimLogger, "Invalid filename or filename extension, must be <name>.particles or <name>.cuboids.");
          //std::cout << "Invalid filename or filename extension, must be <name>.particles or <name>.cuboids." << std::endl;
          help(argsv);
          return -1;
      }
  } else if(input_method == "-c" || input_method == "--cuboids"){

      int num_cuboids = std::stoi(argsv[4]);
      if (argc != num_cuboids * 11 + 5) {           //11 cuboid parameters (w/O mean value of Brownian Motion)
          LOG4CXX_FATAL(molsimLogger, "Faulty cuboid data input");
          //std::cout << "Faulty cuboid data input" << std::endl;
          help(argsv);
          return -1;
      }

      Cuboid c = Cuboid();
      std::array<double, 3> pos = {0, 0, 0},
                v = {0, 0, 0};
      std::array<int, 3> c_size = {0, 0, 0};
      double h = 0, m = 0;

      int offset = 5; //offset of cuboid data in command line args

      for(int i = 0; i < num_cuboids; i++){
          pos = {std::stod(argsv[offset + 0]), std::stod(argsv[offset + 1]), std::stod(argsv[offset + 2])};
          c_size = {std::stoi(argsv[offset + 3]), std::stoi(argsv[offset + 4]), std::stoi(argsv[offset + 5])};
          h = std::stod(argsv[offset + 6]);
          m = std::stod(argsv[offset + 7]);
          v = {std::stod(argsv[offset + 8]), std::stod(argsv[offset + 9]), std::stod(argsv[offset + 10])};

          c = Cuboid(pos, c_size, h, m, v, 0); // meanV is set to hard-coded value by Cuboid constructor regardless of passed value
          particleGenerator.addCuboid(c);

          offset += 11; //next cuboid
      }

      particleContainer = particleGenerator.getParticles();
  } else {
      LOG4CXX_FATAL(molsimLogger, "Erroneous programme call: unsupported input_method");
      //std::cout << "Erroneous programme call!" << std::endl;
      help();
  }

  particleContainer.iterate(
          [] (Particle &p) {
              p.updateDT(delta_t);
          });

  int iteration = 0;
  plotParticles(0, particleContainer.getParticles());

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < t_end) {
    // calculate new x
    particleContainer.iterate([](Particle &p){
      p.calculateX();
      p.saveOldF();
    });
    // calculate new f
    particleContainer.iteratePairs(calculateLennardJones);
    // calculate new v
    particleContainer.iterate([](Particle &p){
      p.calculateV();
    });

    iteration++;
    if (iteration % 10 == 0) {
      plotParticles(iteration, particleContainer.getParticles());
    }

    LOG4CXX_INFO(molsimFileLogger, "Iteration " << iteration << " finished.");
    //std::cout << "Iteration " << iteration << " finished." << std::endl;

    current_time += delta_t;
  }

    LOG4CXX_INFO(molsimLogger, "output written. Terminating...");
  //std::cout << "output written. Terminating..." << std::endl;
  return 0;
}



void plotParticles(int iteration, std::vector<Particle> &particles) {

    /* output in xyz format */

//    std::string out_name_xyz("MD_xyz");
//    outputWriter::XYZWriter writer;
//    writer.plotParticles(particles, out_name_xyz, iteration);

    /* VTK output */

    std::string out_name_vtk("MD_vtk");
    outputWriter::VTKWriter vtkWriter;

    vtkWriter.initializeOutput(particles.size());

    for(auto &p : particles) {
        vtkWriter.plotParticle(p);
    }

    vtkWriter.writeFile(out_name_vtk, iteration);
}

void help(char *argsv[]) {
    /*
    string help = "";
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
     */
    LOG4CXX_INFO(molsimLogger, "This Program should be called as follows:\n" << argsv[0]);
}