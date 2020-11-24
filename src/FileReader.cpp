/*
 * FileReader.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "FileReader.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

FileReader::FileReader() = default;

FileReader::~FileReader() = default;

void FileReader::readParticles(std::vector<Particle> &particles, char *filename) {
  std::array<double, 3> x;
  std::array<double, 3> v;
  double m;
  int num_particles = 0;

  std::ifstream input_file(filename);
  std::string tmp_string;

  if (input_file.is_open()) {

    getline(input_file, tmp_string);
    std::cout << "Read line: " << tmp_string << std::endl;

    while (tmp_string.empty() or tmp_string[0] == '#') {
      getline(input_file, tmp_string);
      std::cout << "Read line: " << tmp_string << std::endl;
    }

    std::istringstream numstream(tmp_string);
    numstream >> num_particles;

    //reserve mem for vector as to not destruct/generate particles
    //while adding to vector
    particles.reserve(num_particles);

    std::cout << "Reading " << num_particles << "." << std::endl;
    getline(input_file, tmp_string);
    std::cout << "Read line: " << tmp_string << std::endl;

    for (int i = 0; i < num_particles; i++) {
      std::istringstream datastream(tmp_string);

      for (auto &xj : x) {
        datastream >> xj;
      }
      for (auto &vj : v) {
        datastream >> vj;
      }
      if (datastream.eof()) {
        std::cout
            << "Error reading file: eof reached unexpectedly reading from line "
            << i << std::endl;
        exit(-1);
      }
      datastream >> m;
      particles.emplace_back(x, v, m);

      getline(input_file, tmp_string);
      std::cout << "Read line: " << tmp_string << std::endl;
    }
  } else {
    std::cout << "Error: could not open file " << filename << std::endl;
    exit(-1);
  }
}

void FileReader::readCuboids(std::vector<Cuboid> &cuboids, char *filename) {
    std::array<double, 3> x;
    std::array<int, 3> size;
    double d;
    double m;
    std::array<double, 3> v;

    int num_cuboids = 0;

    std::ifstream input_file(filename);
    std::string tmp_string;

    if (input_file.is_open()) {

        getline(input_file, tmp_string);
        std::cout << "Read line: " << tmp_string << std::endl;

        while (tmp_string.empty() or tmp_string[0] == '#') {
            getline(input_file, tmp_string);
            std::cout << "Read line: " << tmp_string << std::endl;
        }

        std::istringstream numstream(tmp_string);
        numstream >> num_cuboids;

        //reserve mem for vector as to not destruct/generate particles
        //while adding to vector
        cuboids.reserve(num_cuboids);

        std::cout << "Reading " << num_cuboids << "." << std::endl;
        getline(input_file, tmp_string);
        std::cout << "Read line: " << tmp_string << std::endl;

        for (int i = 0; i < num_cuboids; i++) {
            std::istringstream datastream(tmp_string);

            for (auto &xj : x) {
                datastream >> xj;
            }
            for (auto &sj : size) {
                datastream >> sj;
            }
            if (datastream.eof()) {
                std::cout
                        << "Error reading file: eof reached unexpectedly reading from line "
                        << i << std::endl;
                exit(-1);
            }
            datastream >> d;
            datastream >> m;
            for (auto &vj : v) {
                datastream >> vj;
            }
            cuboids.emplace_back(x, size, d, m, v, MEAN_BROWNIAN);

            getline(input_file, tmp_string);
            std::cout << "Read line: " << tmp_string << std::endl;
        }
    } else {
        std::cout << "Error: could not open file " << filename << std::endl;
        exit(-1);
    }
}


