/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include "particle/Particle.h"
#include "shapes/Cuboid.h"

#include <vector>

class FileReader {

public:
  FileReader();
  virtual ~FileReader();

  /**
   * @brief Reads Particle data from file and constructs Particles into given vector
   * @param particles Vector where the constructed Particles are stored
   * @param filename Name of file with data
   */
  void readParticles(std::vector<Particle> &particles, const char *filename);

  /**
   * @brief Reads Cuboid data from file and constructs Cuboids into given vector
   * @param cuboids Vector where the constructed Cuboids are stored
   * @param filename Name of file with data
   */
  void readCuboids(std::vector<Cuboid> &cuboids, const char *filename);
};
