//
// Created by denis on 14.12.20.
//
#pragma once

#include <xml/molsimInput.hxx>
#include "ParticleContainer.h"
#include "ParticleGenerator.h"

class Simulation {
private:
    /**
     * Input data.
     */
    molsimInput& data;

    /**
     * Container for particles.
     */
    ParticleContainer particleContainer;

    /**
     * Plot the particles to a vtu-file.
     * @param iteration Iteration counter
     * @param particles Vector of particles to be plotted
     * @return
     */
    void plotParticles(int iteration);
public:
    /**
     * Simulation constructor.
     * @param data Input file data
     */
    Simulation(molsimInput &data);

    /**
     * Start simulation.
     * @param isPT Is simulation run a performance test.
     */
    void start(bool isPT);
};