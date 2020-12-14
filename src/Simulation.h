//
// Created by denis on 14.12.20.
//
#pragma once

#include <xml/molsimInput.hxx>
#include "ParticleContainer.h"
#include "ParticleGenerator.h"

class Simulation {
private:
    molsimInput& data;
    ParticleContainer particleContainer;
    void plotParticles(int iteration);
public:
    /**
     * Simulation constructor.
     * @param xmlFile
     */
    Simulation(molsimInput &data);
    void start();
};