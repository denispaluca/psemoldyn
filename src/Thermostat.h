//
// Created by denis on 27.12.20.
//

#pragma once
#include "xml/molsimInput.hxx"
#include "particle/ParticleContainer.h"

class Thermostat {
    /**
     * Number of dimensions.
     */
    int dimensions;

    /**
     * Initial temperature.
     */
    double t_init;

    /**
     * Target temperature.
     */
    double t_target;

    /**
     * Delta temperature.
     */
    thermostat_type::temp_delta_optional t_delta;

    /**
     * The number of time steps after which the thermostat is periodically applied.
     */
    int steps;

    /**
     * Will the brownian motion be changed initially.
     */
    bool change_brownian;

    /**
     * Will Y velocity be scaled.
     */
    bool scaleY;
public:
    /**
     * Consturcutor for thermostat.
     * @param data Thermostat data from xml.
     * @param is3D Is the simulation 3D.
     */
    Thermostat(thermostat_type data, bool is3D);

    /**
     * Scale particles of the input container.
     * @param particles Container with the particles.
     */
    void scale(Container& particles);

    /**
     * Getter for change_brownian.
     * @return change_brownian
     */
    bool changeBrownian() const;

    /**
     * Applies Brownian Mation with factor to the particles.
     * @param particles
     */
    void applyBrownian(ParticleContainer& particles);

    /**
     * Getter for steps.
     * @return steps
     */
    int getSteps() const;

    /**
     * Gets temperature of system of particles.
     * @param particles Container of the system.
     * @return Temperature of system.
     */
    double getCurrentTemp(Container& particles) const;

    /**
     * Getter for initial temperature.
     * @return Initial temperature.
     */
    double getInitTemp() const;
};