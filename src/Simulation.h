//
// Created by denis on 14.12.20.
//
#pragma once

#include <xml/molsimInput.hxx>
#include "particle/ParticleContainer.h"
#include "particle/ParticleGenerator.h"
#include "Container.h"
#include "Thermostat.h"

class Simulation {
private:
    /**
     * Input data.
     */
    molsimInput& data;

    /**
     * Container for particles.
     */
    Container *container;

    /**
     * Thermostat for current simulation.
     */
    Thermostat *thermostat;

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