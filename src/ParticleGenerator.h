//
// Created by mira on 24.11.20.
//

#pragma once

#include <vector>
#include "ParticleContainer.h"
#include "Cuboid.h"
#include <xml/molsimInput.hxx>

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
     * @brief Constructs ParticleGenerator by reading the data from xml file.
     * @param filename Name of the file which will be parsed.
     * @return
     */
    ParticleGenerator(particle_data& data);

    /**
     * @brief Getter for vector of Cuboids
     * @return Vector of Cuboids
     */
    std::vector<Cuboid> getCuboids();

    /**
     * @brief Getter for ParticleContainer with generated particles
     * @return ParticleContainer
     */
    ParticleContainer& getParticles();

    /**
     * @brief adds Cuboid to vector and generates + adds its particles to the ParticleContainer
     * @param c the Cuboid to be added
     */
    void addCuboid(Cuboid c);

};
