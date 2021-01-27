//
// Created by denis on 01.12.20.
//

#pragma once

#include <particle/Particle.h>

/*
 * Calculate force between 2 particles and add it
 * to their respective forces.
 *
 * @param p1 First Particle
 * @param p2 Second Particle
 * @return

void calculateF(Particle &p1, Particle &p2);
*/

/**
 * Calculate Lennard-Jones force between 2 particles and add it
 * to their respective forces.
 *
 * @param p1 First Particle
 * @param p2 Second Particle
 * @return
 */
void calculateLennardJones(Particle &p1, Particle &p2, double epsilon, double sigma);

#ifdef _OPENMP
void cljParallel(Particle &p1, Particle &p2, double epsilon, double sigma, bool useLocks);
#endif