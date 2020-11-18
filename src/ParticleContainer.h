//
// Created by denis on 10.11.20.
//

#ifndef PSEMOLDYN_GROUPB_PARTICLECONTAINER_H
#define PSEMOLDYN_GROUPB_PARTICLECONTAINER_H

#include "Particle.h"
#include <vector>
class ParticleContainer {
private:
    /**
     * List of particles
     */
    std::vector<Particle> particles;
public:
    /**
     * Empty init container
     */
    ParticleContainer();
    /**
     * Init container with vector of particles.
     */
    ParticleContainer(std::vector<Particle>&);
    /**
     * Init container with filename of file to be parsed.
     * @param filename
     */
    ParticleContainer(char* filename);
    /**
     * Returns vector of particles in container.
     * @param
     * @return The vector of particles
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
     */
    void iteratePairs(void (*f)(Particle&,Particle&));
};


#endif //PSEMOLDYN_GROUPB_PARTICLECONTAINER_H
