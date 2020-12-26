//
// Created by denis on 16.12.20.
//

#pragma once
#include "xml/molsimInput.hxx"
#include "particle/Particle.h"

enum Boundary{
    top, bottom, front, back, left, right
};

class BoundaryHandler {
private:
    /**
     * A Particle that will be used as counterparticle for the reflection force calculation.
     */
    Particle counter = Particle({0, 0, 0}, {0, 0, 0}, 0, 0);

    /**
     * The boundary condition of each boundary
     */
    boundaries_type boundary;

    /**
     * The size of the bounded domain
     */
    std::array<double, 3> dimensions{};

    /**
     * Sets counterparticle and calculates force between given particle + counterparticle if Particle is close enough to boundary.
     * @param p the Particle to be reflected
     * @param b the specific boundary to which the Particle is close
     */
    void handleBoundary(Particle& p, Boundary b);

    /**
     * Initializes counterparticle with mass and position of given particle.
     * @param p
     */
    void prepareCounter(Particle& p);
public:

    /**
     * Constructor for BoundaryHandler
     * @param boundary contains the boundary conditions for each side
     * @param dimensions the size of the bounded domain
     */
    BoundaryHandler(boundaries_type& boundary, std::array<double, 3> dimensions);
    void applyForce(Particle& p);
};
