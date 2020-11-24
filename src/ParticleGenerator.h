//
// Created by mira on 24.11.20.
//

#ifndef PSEMOLDYN_GROUPB_PARTICLEGENERATOR_H
#define PSEMOLDYN_GROUPB_PARTICLEGENERATOR_H

#include <vector>
#include "ParticleContainer.h"
#include "Cuboid.h"

class ParticleGenerator{
private:
    /**
     * @brief Vector of all generated cuboids
     */
    std::vector<Cuboid> cuboids;

    /**
     * @brief ParticleContainer with all particles from all generated cuboids
     */
    ParticleContainer particles;
public:
    /**
     * @brief Constructs ParticleGenerator with empty Cuboid vector and ParticleContainer
     */
    ParticleGenerator();

    /**
     * @brief Constructs ParticleGenerator by reading Cuboid parameters from file.
     * @param filename Name of the file which will be parsed.
     * @return
     */
    explicit ParticleGenerator(char* filename);

    /**
     * @brief Getter for vector of Cuboids
     * @return Vector of Cuboids
     */
    std::vector<Cuboid> getCuboids();

    /**
     * @brief Getter for ParticleContainer with generated particles
     * @return ParticleContainer
     */
    ParticleContainer getParticles();

};



#endif //PSEMOLDYN_GROUPB_PARTICLEGENERATOR_H
