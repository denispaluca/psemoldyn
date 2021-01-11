//
// Created by denis on 10.11.20.
//

#include <utils/ForceUtils.h>
#include "ParticleContainer.h"
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <cmath>

using namespace log4cxx;
using namespace log4cxx::helpers;


log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("molsim.console"));

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

void ParticleContainer::erase(int i) {
    particles.erase(particles.begin() + i);
}

void ParticleContainer::calculateIteration(){
    iterate([](Particle &p){
        p.calculateX();
        p.saveOldF();
    });
    // calculate new f
    //iteratePairs(calculateLennardJones);
    iteratePairs([&](Particle &p1, Particle &p2){
        double epsilon = mixedEpsilon.find({p1.getEpsilon(), p2.getEpsilon()})->second;
        double sigma = mixedSigma.find({p1.getSigma(), p2.getSigma()})->second;
        calculateLennardJones(p1, p2, epsilon, sigma);
    });
    // calculate new v
    iterate([](Particle &p){
        p.calculateV();
    });
}

std::vector<Particle>& ParticleContainer::getParticles() {
    return particles;
}

ParticleContainer::~ParticleContainer() {
    LOG4CXX_INFO(logger, "ParticleCONTAINER destructed!");
}

std::size_t ParticleContainer::size() {
    return particles.size();
}

void ParticleContainer::mixParameters() {
    iteratePairs([&](Particle &p1, Particle &p2){
        double eps1 = p1.getEpsilon();
        double eps2 = p2.getEpsilon();
        if(this->mixedEpsilon.find({eps1, eps2}) == this->mixedEpsilon.end()) {
            // mix epsilons and save in map
            this->mixedEpsilon.insert(std::pair<std::array<double, 2>, double>({eps1, eps2}, std::sqrt(eps1*eps2)));
        }

        double sig1 = p1.getSigma();
        double sig2 = p2.getSigma();
        if(this->mixedSigma.find({sig1, sig2}) == this->mixedSigma.end()) {
            // mix sigmas and save in map
            this->mixedSigma.insert(std::pair<std::array<double, 2>, double>({sig1, sig2}, (sig1+sig2)/2));
        }
    });
}