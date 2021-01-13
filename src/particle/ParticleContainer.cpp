//
// Created by denis on 10.11.20.
//

#include <utils/ForceUtils.h>
#include "ParticleContainer.h"
#include <cmath>

#ifdef WITH_LOG4CXX
    #include <log4cxx/logger.h>
    #include <log4cxx/propertyconfigurator.h>

    using namespace log4cxx;
    using namespace log4cxx::helpers;

    //static logger variable molsimLogger
    log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("molsim.console"));
#endif

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
#ifdef WITH_LOG4CXX
    LOG4CXX_INFO(logger, "ParticleCONTAINER destructed!");
#endif
}

std::size_t ParticleContainer::size() {
    return particles.size();
}

void ParticleContainer::mixParameters() {
    iteratePairs([&](Particle &p1, Particle &p2){
        double e1 = p1.getEpsilon();
        double e2 = p2.getEpsilon();
        if(this->mixedEpsilon.find(std::make_pair(e1, e2)) == this->mixedEpsilon.end()) {
            // mix epsilons and save in map
            mixedEpsilon.insert(std::make_pair(std::make_pair(e1, e2), std::sqrt(e1*e2)));
        }

        double s1 = p1.getSigma();
        double s2 = p2.getSigma();
        if(this->mixedSigma.find(std::make_pair(s1, s2)) == this->mixedSigma.end()) {
            // mix sigmas and save in map
            mixedSigma.insert(std::make_pair(std::make_pair(s1, s2), (s1+s2)/2));
        }
    });
}