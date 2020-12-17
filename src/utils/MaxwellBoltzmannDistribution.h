/*
 * MaxwellBoltzmannDistribution.h
 *
 * @Date: 01.10.2010
 * @Author: eckhardw
 */

#pragma once

#include "particle/Particle.h"

/**
 * Add a random velocity according to the Maxwell-Boltzmann distribution to the
 * particles, with a given mean velocity.
 *
 * @p The particle to initialize.
 * @meanVelocity The mean velocity of the brownian motion for the particle.
 * @dimensions The number of dimensions to initialize (2 or 3).
 */
void MaxwellBoltzmannDistribution(Particle& p, double factor, int dimensions);
