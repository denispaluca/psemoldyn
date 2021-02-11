//
// Created by denis on 14.12.20.
//

#pragma once

#include <shapes/ParticleSphere.h>
#include <shapes/Cuboid.h>
#include "xml/molsimInput.hxx"
#include "Container.h"

std::array<int, 3> mapIntVec(integer_vector& x);
std::array<double, 3> mapDoubleVec(double_vector& x);
integer_vector mapToIntVec(std::array<int, 3> x);
double_vector mapToDoubleVec(std::array<double, 3> x);
Cuboid mapCuboid(cuboid& c);

/**
 * Map particle from xsd to ParticleSphere
 * @param c
 * @return
 */
ParticleSphere mapParticleSphere(sphere& c);

Particle mapParticle(particle& p);

particle mapParticleToXML(Particle &p);

extraForce mapExtraForce(extra_force& p);