//
// Created by denis on 27.12.20.
//

#include <cmath>
#include "Thermostat.h"
#include "utils/MaxwellBoltzmannDistribution.h"

Thermostat::Thermostat(thermostat_type data, bool is3D) {
    change_brownian = data.change_brownian();
    steps = data.steps();
    dimensions = is3D ? 3 : 2;
    t_init = data.t_init();
    t_target = data.t_target().present() ? data.t_target().get() : t_init;
    t_delta = data.temp_delta();
}

void Thermostat::applyBrownian(ParticleContainer &particles) {
    particles.iterate([&](Particle &p){
        auto factor = sqrt(t_init/p.getM());
        MaxwellBoltzmannDistribution(p, factor, dimensions);
    });
}

void Thermostat::scale(Container &particles) {
    int nrParticles = particles.size();
    double sumMNormV = 0;
    particles.iterate([&](Particle &p){
        auto &v = p.getV();
        sumMNormV += p.getM()*(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    });

    auto t_current = sumMNormV/(dimensions * nrParticles);

    double t_new;
    if(t_delta.present() && std::abs(t_target - t_current) > std::abs(t_delta.get()))
        t_new = t_current + std::abs(t_delta.get());
    else
        t_new = t_target;

    double scalar = sqrt(t_new/t_current);

    particles.iterate([scalar](Particle &p){
        auto &v = p.getV();
        v[0] *= scalar;
        v[1] *= scalar;
        v[2] *= scalar;
    });
}

bool Thermostat::changeBrownian() {
    return change_brownian;
}

int Thermostat::getSteps() const {
    return steps;
}
