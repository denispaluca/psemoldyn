
#include "FileReader.h"
#include "utils/ArrayUtils.h"

#include <iostream>
#include <outputWriter/VTKWriter.h>
#include "ParticleContainer.h"
#include "ParticleGenerator.h"
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

constexpr double start_time = 0;
double t_end = 0.0;
double delta_t = 0.0;

/**
 * Main function.
 * @param argc
 * @param argsv
 * @return
 */
int main(int argc, char *argsv[]) {
  std::cout << "Hello from MolSim for PSE!" << std::endl;
  if (argc != 4) {
    std::cout << "Errounous programme call! " << std::endl;
    std::cout << "./MolSim {p filename | c filename} t_end delta_t" << std::endl;
  }

  //TODO: add support for specifying cuboid parameters per command line

  ParticleContainer particleContainer = ParticleContainer();
  ParticleGenerator particleGenerator = ParticleGenerator();

  char generation = argsv[1][0];
  if(generation == 'p'){
      particleContainer = ParticleContainer(argsv[2]);
  } else if(generation == 'c'){
     particleGenerator = ParticleGenerator(argsv[2]);
     particleContainer = particleGenerator.getParticles();
  }

  double current_time = start_time;
  t_end = std::stod(argsv[3]);
  delta_t = std::stod(argsv[4]);

  particleContainer.iterate(
          [] (Particle &p) {
              p.updateDT(delta_t);
          });

  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < t_end) {
    // calculate new x
    particleContainer.iterate([](Particle &p){
      p.calculateX();
      p.saveOldF();
    });
    // calculate new f
    particleContainer.iteratePairs(calculateF);
    // calculate new v
    particleContainer.iterate([](Particle &p){
      p.calculateV();
    });

    iteration++;
    if (iteration % 10 == 0) {
      plotParticles(iteration, particleContainer.getParticles());
    }
    std::cout << "Iteration " << iteration << " finished." << std::endl;

    current_time += delta_t;
  }

  std::cout << "output written. Terminating..." << std::endl;
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
