//
// Created by denis on 14.12.20.
//
#pragma once

#include <xml/molsimInput.hxx>
#include "particle/ParticleContainer.h"
#include "particle/ParticleGenerator.h"
#include "Container.h"
#include "Thermostat.h"
#include "Profiler.h"
#include "utils/XSDMapper.h"

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
     * Stores whether velocity + density profiling is enabled
     */
    bool profiling;

    /**
     * Pointer to Profiler instance
     */
    Profiler *profiler;

    /**
     * Frequency in which profiles are created (# of time steps)
     */
    int profiling_freq;

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
     * @return Number of calculated iterations
     */
    int start(bool isPT);

    /**
     * Generates checkpoint after simulation.
     */
    molsimInput &checkpoint();

    /**
    * Get Number of particles
    */
    int getNumParticles();
};