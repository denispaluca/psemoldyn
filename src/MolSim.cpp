
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

constexpr double start_time = 0;
constexpr double end_time = 1000;
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
  iterator = particles.begin();

  for (auto &p1 : particles) {
    for (auto &p2 : particles) {
      // @TODO: insert calculation of force here!
    }
  }
}

void calculateX() {
  for (auto &p : particles) {
      // @TODO: insert calculation of force here!
  }
}

void calculateV() {
  for (auto &p : particles) {
    // @TODO: insert calculation of force here!
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
