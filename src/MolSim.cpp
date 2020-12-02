
#include "FileReader.h"
#include "utils/ArrayUtils.h"

#include <iostream>
#include <string>
#include <regex>
#include <outputWriter/VTKWriter.h>
#include "ParticleContainer.h"
#include "ParticleGenerator.h"

/*
 * Log4cxx includes
 */
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::helpers;

using namespace std;

#define EPSILON 5.0
#define SIGMA  1.0

/**** forward declaration of the calculation functions ****/

/**
 * Calculate force between 2 particles and add it
 * to their respective forces.
 *
 * @param p1 First Particle
 * @param p2 Second Particle
 * @return
 */
void calculateF(Particle &p1, Particle &p2);

void calculateLennardJones(Particle &p1, Particle &p2);

/**
 * Plot the particles to a vtu-file.
 * @param iteration Iteration counter
 * @param particles Vector of particles to be plotted
 * @return
 */
void plotParticles(int iteration, std::vector<Particle> &particles);

/**
 * Calculate second norm cubed of array with length 3.
 * @param x Input coordinates
 * @return (||x||_2)^3
 */
double radiusPow3(const std::array<double, 3> &x);

/**
 * Output help text for calling the program.
 */
void help();

/**
 * Calculate second norm of array with length 3.
 * @param x Input coordinates
 * @return ||x||_2
 */
double radius(const std::array<double, 3> &x);

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
  //std::cout << "Hello from MolSim for PSE!" << std::endl;

  if(argc == 2 && (std::string(argsv[1]) == "-h" || (std::string(argsv[1]) == "--help"))) {
      help();
      return 0;
  }

  //TODO: change condition
  if (argc < 5) {
      LOG4CXX_FATAL(molsimLogger, "Erroneous program call!");
    help();
    //std::cout << "./MolSim t_end delta_t {-f filename | -c <number of cuboids> <cuboid data>}" << std::endl;
  }

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
          //TODO: log error + input help
          LOG4CXX_FATAL(molsimLogger, "Invalid filename or filename extension, must be <name>.particles or <name>.cuboids.");
          //std::cout << "Invalid filename or filename extension, must be <name>.particles or <name>.cuboids." << std::endl;
          help();
          return -1;
      }
  } else if(input_method == "-c" || input_method == "--cuboid"){

      int num_cuboids = std::stoi(argsv[4]);
      if (argc != num_cuboids * 11 + 5) {           //11 cuboid parameters (w/O mean value of Brownian Motion)
          // TODO: log error + input help
          LOG4CXX_FATAL(molsimLogger, "Faulty cuboid data input");
          //std::cout << "Faulty cuboid data input" << std::endl;
          help();
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

          c = Cuboid(pos, c_size, h, m, v, 0); // TODO: change handling of mean Brownian?
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

void calculateF(Particle &p1, Particle &p2) {
  std::array<double, 3> p1_x = p1.getX(),
    xDiff = p2.getX(), f12;
  xDiff[0] -= p1_x[0];
  xDiff[1] -= p1_x[1];
  xDiff[2] -= p1_x[2];

  double divider = radiusPow3(xDiff), vf;
  // calculate F_ij
  if (divider) {
    vf = (p1.getM() * p2.getM()) / divider;
    f12 = {vf*xDiff[0], vf*xDiff[1], vf*xDiff[2]};
    p1.addF(f12);
    p2.addF({-f12[0], -f12[1], -f12[2]});
  }
}

void calculateLennardJones(Particle &p1, Particle &p2) {
    std::array<double, 3> p1_x = p1.getX(),
            xDiff = p2.getX(), f12;
    xDiff[0] -= p1_x[0];
    xDiff[1] -= p1_x[1];
    xDiff[2] -= p1_x[2];

    double divider = radius(xDiff), vf1, vf2;

    if(divider) {
        vf1 = 24*EPSILON / pow(divider, 2);

        vf2 = pow(SIGMA/divider, 6) - 2*pow(SIGMA/divider, 12);

        f12 = {vf1*vf2*xDiff[0], vf1*vf2*xDiff[1], vf1*vf2*xDiff[2]};

        p1.addF(f12);
        p2.addF({-f12[0], -f12[1], -f12[2]});
    }

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

double radiusPow3(const std::array<double, 3> &x) {
    double result = x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
    return pow(sqrt(result), 3);
}

void help() {
    string help = "This Program should be called as follows:\n";
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
    LOG4CXX_INFO(molsimLogger, help);
    /*
    std::cout << std::endl;
    std::cout << "This Program should be called as follows:" << std::endl;
    std::cout << "./MolSim t_end delta_t {-f filename | -c cuboid_number <cuboid_data>...}" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "t_end:         end time of the simulation" << std::endl;
    std::cout << "delta_t:       length of time step between iterations" << std::endl;
    std::cout << "-f, --file:    enables input via file. Accepted file extensions are .particles and .cuboids." << std::endl;
    std::cout << "               The corresponding file formats are specified in the project's ReadMe." << std::endl;
    std::cout << "-c, --cuboid:  allows for direct input of cuboid parameters. The data is expected to be given in the following order:" << std::endl;
    std::cout << "                 <position of cuboid> - 3 double values" << std::endl ;
    std::cout << "                 <number of particles per dimension> - 3 integer values" << std::endl;
    std::cout << "                 <mesh width> - 1 double value" << std::endl;
    std::cout << "                 <mass of 1 particle> - 1 double value" << std::endl;
    std::cout << "                 <initial velocity> - 3 double values" << std::endl;
    std::cout << "               divided by blank spaces and in a single line." << std::endl;
    std::cout << "               Data of multiple cuboids must also be given in a single line with a blank space in between." << std::endl;
    std::cout << "This help text can be printed using ./MolSim -h or ./MolSim --help." << std::endl;
     */
}

double radius(const std::array<double, 3> &x) {
    return x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
}