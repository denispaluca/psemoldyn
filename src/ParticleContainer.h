//
// Created by denis on 10.11.20.
//

#ifndef PSEMOLDYN_GROUPB_PARTICLECONTAINER_H
#define PSEMOLDYN_GROUPB_PARTICLECONTAINER_H

#include "Particle.h"
#include <vector>
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
     * Constructs ParticleContainer by copying particles.
     * @param particles Particles to be copied.
     * @return
     */
    ParticleContainer(std::vector<Particle> &particles);

    /**
     * Constructs ParticleContainer with filename to be parsed by FileReader.
     * @param filename Name of the files which will be parsed.
     * @return
     */
    ParticleContainer(char* filename);

    /**
     * Getter for the vector of particles in container.
     * @return The vector of particles
     * @param
     */
    std::vector<Particle> &getParticles();

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
    void iterate(void (*f)(Particle&));

    /**
     * Iterate over all unique particle pairs and apply function f
     * @param f Function that is applied to pairs
     * @return
     */
    void iteratePairs(void (*f)(Particle&,Particle&));
};


#endif //PSEMOLDYN_GROUPB_PARTICLECONTAINER_H
