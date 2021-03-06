//
// Created by denis on 01.12.20.
//

#pragma once
#include <vector>
#include <Container.h>
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

/**
 * TODO
 * @param p1
 * @param p2
 */
std::array<double, 3> calculateMembraneForce(Particle &p1, Particle &p2, bool diagonal, double x);

/**
 * TODO
 * @param p1
 * @param p2
 * @param particles
 */
void calculateMembrane(Particle &p1, Particle &p2, double epsilon, double sigma);

/**
 * TODO
 * @param particles
 * @param pos
 * @param length
 * @param x
 */
void setNeighbours(std::vector<Particle> &particles, int pos, int length, int x);

#ifdef _OPENMP
void cljParallel(Particle &p1, Particle &p2, double epsilon, double sigma, bool useLocks);
void membraneParallel(Particle &p1, Particle &p2, double epsilon, double sigma, bool locks);
#endif

void applyExtraForces(std::vector<Particle> &particles, std::vector<extraForce> &extraForces, int iteration);