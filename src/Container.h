//
// Created by denis on 15.12.20.
//

#pragma once
#include <functional>
#include "Particle.h"
class Container{
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
    virtual void calculateIteration() = 0;
};