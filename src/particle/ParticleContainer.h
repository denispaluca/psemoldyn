//
// Created by denis on 10.11.20.
//

#pragma once

#include "Particle.h"
#include <vector>
#include <functional>
#include "Container.h"

/**
 * The ParticleContainer class encapsulates particles
 * and makes it possible to iterate through them.
 */
class ParticleContainer : public Container {
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
     * Destructor of particle container.
     * @param
     * @return
     */
    virtual ~ParticleContainer();

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
    void iterate(std::function<void(Particle&)> f) override;

    /**
     * Iterate over all unique particle pairs and apply function f
     * @param f Function that is applied to pairs
     * @return
     */
    void iteratePairs(std::function<void(Particle&, Particle&)> f) override;

    /**
     * Requests that the particles vector capacity be at least enough to contain n elements.
     * @param n Minimum capacity for the particles vector.
     * @return
     */
    void reserve(std::size_t n);

    std::vector<Particle>& getParticles();

    /**
     * Erase particle at position i.
     * @param i Position
     */
     void erase(int i);

    /**
    * Size of particles vector.
    */
     std::size_t size() override;

     //TODO
     void mixParameters();

    //void calculateIteration();

    void calculateIteration(int d);

    //void setNeighbours(int pos, int length, int x);
};
