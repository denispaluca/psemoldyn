//
// Created by denis on 10.11.20.
//

#pragma once

#include "Particle.h"
#include <vector>
#include <functional>

/**
 * The ParticleContainer class encapsulates particles
 * and makes it possible to iterate through them.
 */
class ParticleContainer {
private:
    /**
     * Vector of particles
     */
    std::vector<Particle> particles;
public:
    /**
     * Constructs ParticleContainer with empty vector of particles.
     * @return
     * @param
     */
    ParticleContainer();

    /**
     * Constructs ParticleContainer with filename to be parsed by FileReader.
     * @param particles Vector of particles.
     * @return
     */
    ParticleContainer(std::vector<Particle> &particles);

    /**
     * Push particle at the end of the vector.
     * @param particle The particle pushed in particles vector
     * @return
     */
    void push(Particle &particle);

    /**
     * Iterate over all particles and apply function f
     * @param f Function applied to particles
     * @return
     */
    void iterate(std::function<void(Particle&)> f);

    /**
     * Iterate over all unique particle pairs and apply function f
     * @param f Function that is applied to pairs
     * @return
     */
    void iteratePairs(std::function<void(Particle&, Particle&)> f);

    /**
     * Requests that the particles vector capacity be at least enough to contain n elements.
     * @param n Minimum capacity for the particles vector.
     * @return
     */
    void reserve(std::size_t n);

    size_t size();
};
