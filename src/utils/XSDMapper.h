//
// Created by denis on 14.12.20.
//

#pragma once

#include <Cuboid.h>
#include <ParticleSphere.h>
#include "xml/molsimInput.hxx"

std::array<int, 3> mapIntVec(integer_vector& x);
std::array<double, 3> mapDoubleVec(double_vector& x);
Cuboid mapCuboid(cuboid& c);

/**
 * Map particle from xsd to ParticleSphere
 * @param c
 * @return
 */
ParticleSphere mapParticleSphere(sphere& c);

Particle mapParticle(particle& p);