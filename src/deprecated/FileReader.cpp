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

#ifdef WITH_LOG4CXX
    #include <log4cxx/logger.h>
    #include <log4cxx/propertyconfigurator.h>

    using namespace log4cxx;
    using namespace log4cxx::helpers;

    //static logger variable fileReaderLogger
    log4cxx::LoggerPtr fileReaderLogger(log4cxx::Logger::getLogger("filereader"));
#endif

FileReader::FileReader() = default;

FileReader::~FileReader() = default;

void FileReader::readParticles(std::vector<Particle> &particles, const char *filename) {
  std::array<double, 3> x;
  std::array<double, 3> v;
  double m;
  int num_particles = 0;

  std::ifstream input_file(filename);
  std::string tmp_string;

  if (input_file.is_open()) {

    getline(input_file, tmp_string);

    #ifdef WITH_LOG4CXX
      LOG4CXX_DEBUG(fileReaderLogger, "Read line: " << tmp_string);
    #endif

    while (tmp_string.empty() or tmp_string[0] == '#') {
      getline(input_file, tmp_string);
        #ifdef WITH_LOG4CXX
            LOG4CXX_DEBUG(fileReaderLogger, "Read line: " << tmp_string);
        #endif

    }

    std::istringstream numstream(tmp_string);
    numstream >> num_particles;

    //reserve mem for vector as to not destruct/generate particles
    //while adding to vector
    particles.reserve(num_particles);
    #ifdef WITH_LOG4CXX
      LOG4CXX_DEBUG(fileReaderLogger, "Reading " << num_particles << ".");
    #endif

    getline(input_file, tmp_string);

    #ifdef WITH_LOG4CXX
      LOG4CXX_DEBUG(fileReaderLogger, "Read line: " << tmp_string);
    #endif

    for (int i = 0; i < num_particles; i++) {
      std::istringstream datastream(tmp_string);

      for (auto &xj : x) {
        datastream >> xj;
      }
      for (auto &vj : v) {
        datastream >> vj;
      }
      if (datastream.eof()) {
#ifdef WITH_LOG4CXX
          LOG4CXX_FATAL(fileReaderLogger, "Error reading file: eof reached unexpectedly reading from line " << i);
#endif

        exit(-1);
      }
      datastream >> m;
      particles.emplace_back(x, v, m,5,1);

      getline(input_file, tmp_string);
#ifdef WITH_LOG4CXX
        LOG4CXX_DEBUG(fileReaderLogger, "Read line: " << tmp_string);
#endif

    }
  } else {
#ifdef WITH_LOG4CXX
      LOG4CXX_FATAL(fileReaderLogger, "Error: could not open file " << filename);
#endif

    exit(-1);
  }
}

void FileReader::readCuboids(std::vector<Cuboid> &cuboids, const char *filename) {
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
#ifdef WITH_LOG4CXX
        LOG4CXX_DEBUG(fileReaderLogger, "Read line: " << tmp_string);
#endif


        while (tmp_string.empty() or tmp_string[0] == '#') {
            getline(input_file, tmp_string);
#ifdef WITH_LOG4CXX
            LOG4CXX_DEBUG(fileReaderLogger, "Read line: " << tmp_string);
#endif

        }

        std::istringstream numstream(tmp_string);
        numstream >> num_cuboids;

        //reserve mem for vector as to not destruct/generate particles
        //while adding to vector
        cuboids.reserve(num_cuboids);
#ifdef WITH_LOG4CXX
        LOG4CXX_DEBUG(fileReaderLogger, "Reading " << num_cuboids << ".");
#endif
        getline(input_file, tmp_string);
#ifdef WITH_LOG4CXX
        LOG4CXX_DEBUG(fileReaderLogger, "Read line: " << tmp_string);
#endif

        for (int i = 0; i < num_cuboids; i++) {
            std::istringstream datastream(tmp_string);

            for (auto &xj : x) {
                datastream >> xj;
            }
            for (auto &sj : size) {
                datastream >> sj;
                if(sj < 0) {
#ifdef WITH_LOG4CXX
                    LOG4CXX_FATAL(fileReaderLogger, "Error reading file: negative cuboid size found in line " << i);
#endif
                    exit(-1);
                }
            }
            if (datastream.eof()) {
#ifdef WITH_LOG4CXX
                LOG4CXX_FATAL(fileReaderLogger, "Error reading file: eof reached unexpectedly reading from line " << i);
#endif
                exit(-1);
            }
            datastream >> d;
            if(d < 0) {
#ifdef WITH_LOG4CXX
                LOG4CXX_FATAL(fileReaderLogger, "Error reading file: negative distance found in line " << i);
#endif
                exit(-1);
            }
            datastream >> m;
            if(m < 0) {
#ifdef WITH_LOG4CXX
                LOG4CXX_FATAL(fileReaderLogger, "Error reading file: negative mass found in line " << i);
#endif
                exit(-1);
            }
            for (auto &vj : v) {
                datastream >> vj;
            }
            cuboids.emplace_back(x, size, d, m, v, 5, 1, false, 0, 0, 0);

            getline(input_file, tmp_string);
#ifdef WITH_LOG4CXX
            LOG4CXX_DEBUG(fileReaderLogger, "Read line: " << tmp_string);
#endif
        }
    } else {
#ifdef WITH_LOG4CXX
        LOG4CXX_FATAL(fileReaderLogger, "Error: could not open file " << filename);
#endif
        exit(-1);
    }
}


