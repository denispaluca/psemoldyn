//
// Created by denis on 15.12.20.
//

#pragma once
#include <functional>
#include <map>
#include "particle/Particle.h"

struct extraForce {
    int index;
    int iteration;
    std::array<double, 3> force;
};

class Container{
protected:
    std::map<std::pair<double, double>, double> mixedEpsilon;

    std::map<std::pair<double, double>, double> mixedSigma;

public:
    /**
     * Iterate over all particles and apply function f
     * @param f Function applied to particles
     * @return
     */
    virtual void iterate(std::function<void(Particle&)> f) = 0;

    /**
     * Iterate over all unique particle pairs and apply function f
     * @param f Function that is applied to pairs
     * @return
     */
    virtual void iteratePairs(std::function<void(Particle&, Particle&)> f) = 0;

    /**
     * Does one iteration step with the particles.
     */
    virtual void calculateIteration(int d) = 0;

    /**
     * Size of particles vector.
     */
    virtual std::size_t size() = 0;

    /**
     * Calculates the mixed LJ parameters for all particle type combinations in the Container
     * and stores them in mixedEpsilon and mixedSigma respectively
     */
    virtual void mixParameters() = 0;

    /**
     * Returns a map of epsilon pairs to the mixed epsilon
     * @return the map
     */
    virtual std::map<std::pair<double, double>, double> getMixedEpsilon();

    /**
     * Returns a map of sigma pairs to the mixed sigma
     * @return the map
     */
    virtual std::map<std::pair<double, double>, double> getMixedSigma();

    /*
     * Apply additional forces to specific particles by index
    */
    std::vector<extraForce> extraForces;


};