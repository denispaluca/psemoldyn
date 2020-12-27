//
// Created by mira on 24.11.20.
//

#pragma once

#include <vector>
#include "ParticleContainer.h"
#include "shapes/Cuboid.h"
#include "shapes/ParticleSphere.h"
#include <xml/molsimInput.hxx>
#include <Thermostat.h>

class ParticleGenerator{
private:
    /**
     * @brief Vector of all generated cuboids
     */
    std::vector<Cuboid> cuboids;

    /**
    * @brief Vector of all generated particleSpheres
    */
    std::vector<ParticleSphere> particleSpheres;

    /**
     * @brief ParticleContainer with all particles from all generated cuboids
     */
    ParticleContainer particles;

    /**
     * XML Input data used in particle generator.
     */
    particle_data data;

    /**
     * Thermostat for particles.
     */
     Thermostat* thermostat;

    /**
     * Initialize vectors and reserve for particle size.
     */
    void reserve();

    /**
     * Generate particles.
     */
    void generate();

    /**
     * Applies Brownian Motion to generated particles.
     */
     void applyBrownianMotion();
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
    ParticleGenerator(particle_data& data, Thermostat* thermostat);

    /**
     * @brief Getter for vector of Cuboids
     * @return Vector of Cuboids
     */
    std::vector<Cuboid> getCuboids();

    /**
     * @brief Getter for vector of ParticleSphere
     * @return Vector of ParticleSphere
     */
    std::vector<ParticleSphere> getParticleSpheres();

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
