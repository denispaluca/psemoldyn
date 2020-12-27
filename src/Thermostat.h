//
// Created by denis on 27.12.20.
//

#pragma once
#include "xml/molsimInput.hxx"
#include "particle/ParticleContainer.h"

class Thermostat {
    int dimensions;
    double t_init;
    double t_target;
    thermostat_type::temp_delta_optional t_delta;
    int steps;
    bool change_brownian;
public:
    Thermostat(thermostat_type data, bool is3D);
    void scale(Container& particles);
    bool changeBrownian();
    void applyBrownian(ParticleContainer& particles);
    int getSteps() const;
};