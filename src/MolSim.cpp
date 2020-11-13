
#include "FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "utils/ArrayUtils.h"

#include <iostream>
#include <list>
#include <outputWriter/VTKWriter.h>

/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 */
void calculateF();

/**
 * calculate the position for all particles
 */
void calculateX();

/**
 * calculate the position for all particles
 */
void calculateV();

/**
 * plot the particles to a xyz-file
 */
void plotParticles(int iteration);

/**
 * Calculate (||x_i - x_j||_2)^3
 */
double radiusPow3(std::array<double, 3> &xi, std::array<double, 3> &xj);

constexpr double start_time = 0;
constexpr double end_time = 2;
constexpr double delta_t = 0.014;

std::list<Particle> particles;

int main(int argc, char *argsv[]) {

  std::cout << "Hello from MolSim for PSE!" << std::endl;
  if (argc != 2) {
    std::cout << "Errounous programme call! " << std::endl;
    std::cout << "./molsym filename" << std::endl;
  }

  FileReader fileReader;
  fileReader.readFile(particles, argsv[1]);

  double current_time = start_time;

  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < end_time) {
    // calculate new x
    calculateX();
    // calculate new f
    calculateF();
    // calculate new v
    calculateV();

    iteration++;
    if (iteration % 10 == 0) {
      plotParticles(iteration);
    }
    std::cout << "Iteration " << iteration << " finished." << std::endl;

    current_time += delta_t;
  }

  std::cout << "output written. Terminating..." << std::endl;
  return 0;
}

void calculateF() {
  std::list<Particle>::iterator iterator;
  std::array<double, 3> p1_x, p2_x, p1_f;
  double p1_m, p2_m, vf;
  int i;

  iterator = particles.begin();

  for (auto &p1 : particles) {
    p1_x = p1.getX();
    p1_f = {0., 0., 0.};
    p1_m = p1.getM();
    for (auto &p2 : particles) {
      // calculate F_ij
      p2_x = p2.getX();
      if (p1_x[0] != p2_x[0] || p1_x[1] != p2_x[1] || p1_x[2] != p2_x[2]) {
          p2_m = p2.getM();
          vf = (p1_m * p2_m) / radiusPow3(p1_x, p2_x);
          for (i=0; i<3; i++){
              p1_f[i] += vf * (p2_x[i] - p1_x[i]);
          }
      }
    }
    p1.setF(p1_f);
  }
}

void calculateX() {
  for (auto &p : particles) {
      // @TODO: insert calculation of force here!
      p.calculateX();
  }
}

void calculateV() {
  for (auto &p : particles) {
    // @TODO: insert calculation of force here!
    p.calculateV();
  }
}

void plotParticles(int iteration) {

    /* output in xyz format */

    std::string out_name_xyz("MD_xyz");
    outputWriter::XYZWriter writer;
    writer.plotParticles(particles, out_name_xyz, iteration);

    /* VTK output */

    std::string out_name_vtk("MD_vtk");
    outputWriter::VTKWriter vtkWriter;

    vtkWriter.initializeOutput(particles.size());

    for(auto &p : particles) {
        vtkWriter.plotParticle(p);
    }

    vtkWriter.writeFile(out_name_vtk, iteration);
}

double radiusPow3(std::array<double, 3> &xi, std::array<double, 3> &xj) {
    double result = 0;
    for (int i = 0; i<3; i++){
        result += pow((xi[i]-xj[i]), 2);
    }
    return pow(sqrt(result), 3);
}
