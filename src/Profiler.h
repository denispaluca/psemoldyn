//
// Created by mira on 29.01.21.
//

#ifndef PSEMOLDYN_GROUPB_PROFILER_H
#define PSEMOLDYN_GROUPB_PROFILER_H

#include "Container.h"
#include "xml/molsimInput.hxx"

class Profiler {
    private:
        /**
         * Number of bins along x-axis
         */
        int num_bins;

        /**
         * Volume of a single bin
         */
        double bin_volume;

        /**
         * Size of one bin
         */
        std::array<double, 3> bin_size;

        /**
         * Path to file in which velocity profile data is written
         */
        std::string velocity_path;

        /**
         * Path to file in which density profile data is written
         */
        std::string density_path;

        /**
         * Pointer to container with all Particles of the Simulation
         */
        Container *container;

        /**
         * Vector used for calculating average velocity per bin
         */
        std::vector<std::array<double, 3>> velocities;

        /**
        * Vector used for calculating average density per bin
        */
        std::vector<double> densities;

        /**
         * Vector storing the number of Particles per bin
         */
        std::vector<int> binParticles;

        /**
         * Default constructor
         */
        Profiler();

        /**
         * Checks whether instance of this class already exists (for Singleton pattern)
         */
        static bool instanceFlag;

        /**
         * Pointer to the Profiler instance
         */
        static Profiler *single_profiler;
    public:
        /**
         * initializes Profiler with simulation data
         * @param data simulation parameters
         * @param container simulation particles
         */
        void init(molsimInput &data, Container *container);

        /**
         * Calculates profile data based on container and writes them to output files
         */
        void createProfile();

        /**
         * Returns (and if necessary creates) the Profiler instance (Singleton pattern)
         * @return
         */
        static Profiler *getInstance();
};


#endif //PSEMOLDYN_GROUPB_PROFILER_H
