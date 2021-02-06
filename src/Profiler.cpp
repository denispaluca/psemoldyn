//
// Created by mira on 29.01.21.
//

#include <iostream>
#include <array>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include "particle/Particle.h"
#include "Profiler.h"
#include "Container.h"
#include "xml/molsimInput.hxx"


Profiler::Profiler() {

}

bool Profiler::instanceFlag = false;

Profiler* Profiler::single_profiler = NULL;

Profiler* Profiler::getInstance() {
    if (!instanceFlag) {
        single_profiler = new Profiler();
        instanceFlag = true;
        return single_profiler;
    } else {
        return single_profiler;
    }
}

void Profiler::init(molsimInput &data, Container *container) {

    if(data.profiler().present()) {
        num_bins = data.profiler()->profiling_bins();
        velocity_path = data.profiler()->velocity_profile_path();
        density_path = data.profiler()->density_profile_path();
    } else {
        num_bins = 1;
        velocity_path = "vProfile";
        density_path = "dProfile";
    }

    this->container = container;
    bin_size = {data.domain().domain_size().x() / num_bins, data.domain().domain_size().y(), data.domain().domain_size().z()};
    bin_volume = bin_size[0] * bin_size[1] * bin_size[2];
}


void Profiler::createProfile() {

    for(int i = 0; i < num_bins; i++) {
        velocities.push_back({0, 0, 0});
        densities.emplace_back(0.0);
        binParticles.emplace_back(0);
    }

    // sum up velocities/densities/pacrticle numbers
    container->iterate([&](Particle &p){
        int bin = p.x[0] / bin_size[0];
        std::array<double, 3> velo = velocities.at(bin);
        velocities.insert(velocities.begin() + bin, {velo[0] + p.getV()[0], velo[1] + p.getV()[1], velo[2] + p.getV()[2]});
        binParticles.at(bin)++;
        densities.insert(densities.begin() + bin, densities.at(bin) + p.getM());
    });

    std::array<double, 3> none = {0, 0, 0};

    // calculate averages
    for(int i = 0; i < num_bins; i++) {
        if (binParticles.at(i)) {
            velocities.insert(velocities.begin() + i,
                              {velocities.at(i)[0] / binParticles.at(i), velocities.at(i)[1] / binParticles.at(i),
                               velocities.at(i)[2] / binParticles.at(i)});
            densities.insert(densities.begin() + i, densities.at(i) / bin_volume);
        } else {
            velocities.insert(velocities.begin() + i, none);
            densities.insert(densities.begin() + i, 0);
        }
    }

    // write to csv file
    std::ofstream vProfile;
    vProfile.open(velocity_path, std::ios_base::app);

    std::ofstream dProfile;
    dProfile.open(density_path, std::ios_base::app);

    for(int i = 0; i < num_bins; i++) {
        vProfile << "{" << velocities.at(i)[0] << " " << velocities.at(i)[1] << " " << velocities.at(i)[2] << "}";
        dProfile << densities.at(i);
        if (i != num_bins - 1) {
            vProfile << ",";
            dProfile << ",";
        }
    }

    vProfile << std::endl;
    dProfile << std::endl;

    vProfile.close();
    dProfile.close();

    velocities.clear();
    densities.clear();
    binParticles.clear();
}
