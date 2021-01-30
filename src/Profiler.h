//
// Created by mira on 29.01.21.
//

#ifndef PSEMOLDYN_GROUPB_PROFILER_H
#define PSEMOLDYN_GROUPB_PROFILER_H

#include "Container.h"
#include "xml/molsimInput.hxx"

class Profiler {
    private:
        int num_bins;

        double bin_volume;

        std::array<double, 3> bin_size;

        std::string velocity_path;

        std::string density_path;

        Container *container;

        std::vector<std::array<double, 3>> velocities;

        std::vector<double> densities;

        std::vector<int> binParticles;

        Profiler();

        static bool instanceFlag;

        static Profiler *single_profiler;
    public:
        void init(molsimInput &data, Container *container);

        void createProfile();

        static Profiler *getInstance();
};


#endif //PSEMOLDYN_GROUPB_PROFILER_H
