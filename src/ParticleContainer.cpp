//
// Created by denis on 10.11.20.
//

#include "ParticleContainer.h"

ParticleContainer::ParticleContainer() {
  particles = std::vector<Particle>();
}

ParticleContainer::ParticleContainer(std::vector<Particle> &particles) {
  this->particles = particles;
}

std::vector<Particle> &ParticleContainer::getParticles() {
  return particles;
}

void ParticleContainer::push(Particle &particle) {
  particles.emplace_back(particle);
}

void ParticleContainer::iterate(void (*f)(Particle &)) {
  for(auto &particle : particles)
    (*f)(particle);
}

void ParticleContainer::iteratePairs(void (*f)(Particle &, Particle &)) {
  for(auto i = particles.begin(); i != particles.end(); ++i)
    for(auto j = i + 1; j != particles.end(); ++j)
      (*f)(*i,*j);
}

void ParticleContainer::reserve(const int n){
    particles.reserve(n);
}