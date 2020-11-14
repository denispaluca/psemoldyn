
#include "FileReader.h"
#include "utils/ArrayUtils.h"

#include <iostream>
#include <outputWriter/VTKWriter.h>
#include "ParticleContainer.h"
/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 */
void calculateF(Particle &p1, Particle &p2);

/**
 * calculate the position for all particles
 */
void calculateX(Particle &p);

/**
 * calculate the position for all particles
 */
void calculateV(Particle &p);

/**
 * plot the particles to a vtu-file
 */
void plotParticles(int iteration, std::vector<Particle> &particles);

/**
 * Calculate (||x||_2)^3
 */
double radiusPow3(const std::array<double, 3> &x);

constexpr double start_time = 0;
constexpr double end_time = 100;
constexpr double delta_t = 0.014;


int main(int argc, char *argsv[]) {

  std::cout << "Hello from MolSim for PSE!" << std::endl;
  if (argc != 2) {
    std::cout << "Errounous programme call! " << std::endl;
    std::cout << "./molsym filename" << std::endl;
  }

  ParticleContainer particleContainer = ParticleContainer(argsv[1]);

  double current_time = start_time;

  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < end_time) {
    // calculate new x
    particleContainer.iterate(calculateX);
    // calculate new f
    particleContainer.iteratePairs(calculateF);
    // calculate new v
    particleContainer.iterate(calculateV);

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

void calculateX(Particle &p) {
    // @TODO: insert calculation of force here!
    p.calculateX();
    p.saveOldF();
}

void calculateV(Particle &p) {
  // @TODO: insert calculation of force here!
  p.calculateV();
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
