//
// Created by denis on 10.11.20.
//

#ifndef PSEMOLDYN_GROUPB_PARTICLECONTAINER_H
#define PSEMOLDYN_GROUPB_PARTICLECONTAINER_H

#include "Particle.h"
#include <list>
class ParticleContainer {
private:
    /**
     * List of particles
     */
    std::list<Particle> particles;
public:
    ParticleContainer(std::list<Particle>);
    ParticleContainer(const char* filename);
    /**
     * push particle at the end of the list
     * @param particle
     */
    void push(Particle &particle);
    /**
     * Iterate over all particles and apply function f
     * @param f
     */
    void iterate(void (*f)(Particle&));
    /**
     * Iterate over all unique particle pairs and apply function f
     * @param f
     */
    void iteratePairs(void (*f)(Particle&,Particle&));
};


#endif //PSEMOLDYN_GROUPB_PARTICLECONTAINER_H
