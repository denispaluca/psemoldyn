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
        if (!p.fixed) MaxwellBoltzmannDistribution(p, factor, dimensions);
    });
}

void Thermostat::scale(Container &particles) {
    if(particles.size() == 0) return;
    auto t_current = getCurrentTemp(particles);
    if(t_current == t_target) return;

    double t_new;
    if(t_delta.present() && std::abs(t_target - t_current) > std::abs(t_delta.get()))
        t_new = t_target > t_current ?
                t_current + std::abs(t_delta.get()):
                t_current - std::abs(t_delta.get());
    else
        t_new = t_target;

    double scalar = sqrt(t_new/t_current);

    particles.iterate([scalar](Particle &p){
        if(!p.fixed) {
            auto &v = p.getV();
            v[0] *= scalar;
            //v[1] *= scalar;
            v[2] *= scalar;
        }
    });
}

bool Thermostat::changeBrownian() const {
    return change_brownian;
}

int Thermostat::getSteps() const {
    return steps;
}

double Thermostat::getCurrentTemp(Container &particles) const {
    int nrParticles = particles.size();
    if(nrParticles == 0) return 0;

    double meanYV = 0;
    particles.iterate([&](Particle &p){
        meanYV += p.getV()[1];
    });
    meanYV /= nrParticles;

    double sumMNormV = 0;
    particles.iterate([&](Particle &p){
        auto &v = p.getV();
        sumMNormV += p.getM()*(v[0]*v[0] + (v[1] - meanYV)*(v[1] - meanYV) + v[2]*v[2]);
    });

    auto t_current = sumMNormV/(dimensions * nrParticles);
    return t_current;
}

double Thermostat::getInitTemp() const {
    return t_init;
}
