//
// Created by denis on 16.12.20.
//

#pragma once
#include "xml/molsimInput.hxx"
#include "particle/Particle.h"
#include "LinkedCell.h"
#include <functional>

enum Boundaries{
    top, bottom, front, back, left, right
};

typedef boundary_type::value Boundary;

class BoundaryHandler {
private:
    /**
     * A Particle that will be used as counterparticle for the reflection force calculation.
     */
    Particle counter = Particle({0, 0, 0}, {0, 0, 0}, 0, 0);

    std::array<double,3> domainSize;
    std::array<int,3> dimensions;
    std::vector<LinkedCell>* cells;
    int getIndex(std::array<int, 3> pos);
    boundaries_type boundaries;

    /**
     * Initializes counterparticle with mass and position of given particle.
     * @param p
     */
    void prepareCounter(Particle& p);

    void reflect(Boundaries b);
    void period(Boundaries b);
    void handleBoundary(Boundaries boundary, boundary_type& value);
public:

    /**
     * Constructor for BoundaryHandler
     * @param boundary contains the boundary conditions for each side
     * @param l cell container to apply condition.
     */
    BoundaryHandler(boundaries_type boundaries, std::array<double, 3> domainSize,
                    std::array<int, 3> dimensions);
    /**
     * Iterate cells at boundary b and apply function f.
     * @param b Boundary to iterate in.
     * @param f Function to be applied.
     */
    void iterateCellsAtBoundary(Boundaries b, const std::function<void(LinkedCell&)>& f);

    /**
     * Handles all boundary conditions for current lcc configuration.
     */
    void handle(std::vector<LinkedCell>* cells);

    void iterateParticlesAtBoundary(Boundaries b, const std::function<void(Particle&)>& f);
};
