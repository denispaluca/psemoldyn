//
// Created by denis on 10.11.20.
//

#include <utils/ForceUtils.h>
#include "ParticleContainer.h"

ParticleContainer::ParticleContainer() {
  particles = std::vector<Particle>();
}

ParticleContainer::ParticleContainer(std::vector<Particle> particles) {
  this->particles = particles;
}

void ParticleContainer::push(Particle &particle) {
  particles.emplace_back(particle);
}

void ParticleContainer::iterate(std::function<void(Particle&)> f) {
  for(auto &particle : particles)
    f(particle);
}

void ParticleContainer::iteratePairs(std::function<void(Particle&, Particle&)> f) {
  for(auto i = particles.begin(); i != particles.end(); ++i)
    for(auto j = i + 1; j != particles.end(); ++j)
      f(*i,*j);
}

void ParticleContainer::reserve(const std::size_t n){
    particles.reserve(n);
}

int ParticleContainer::size(){
    return particles.size();
}

void ParticleContainer::erase(int i) {
    particles.erase(particles.begin() + i);
}

void ParticleContainer::calculateIteration(){
    iterate([](Particle &p){
        p.calculateX();
        p.saveOldF();
    });
    // calculate new f
    iteratePairs(calculateLennardJones);
    // calculate new v
    iterate([](Particle &p){
        p.calculateV();
    });
}

std::vector<Particle> ParticleContainer::getParticles() {
    return particles;
}
