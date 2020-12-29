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

    /**
     * Size of domain.
     */
    std::array<double,3> domainSize;

    /**
     * Dimensions of cell grid.
     */
    std::array<int,3> dimensions;

    /**
     * Cell vector pointer of cells to be handled.
     */
    std::vector<LinkedCell>* cells;

    /**
     * Calculates index of the LinkedCell containing the given point in space.
     * !!!DUPLICATE!!!
     * @param pos the coordinates
     * @return the index of the LinkedCell
     */
    int getIndex(std::array<int, 3> pos);

    /**
     * Boundaries from the xml file.
     */
    boundaries_type boundaries;

    std::map<std::array<double, 2>, double> *mixedEpsilon;

    std::map<std::array<double, 2>, double> *mixedSigma;

    /**
     * Initializes counterparticle with mass and position of given particle.
     * @param p
     */
    void prepareCounter(Particle& p);

    /**
     * Apply reflection on boundary b.
     * @param b Boundary to reflect particles.
     */
    void reflect(Boundaries b);

    /**
     * Apply periodicity on boundary b.
     * @param b Boundary to apply.
     */
    void period(Boundaries b);

    /**
     * Handles correct function on boundary, according to value.
     * @param boundary Boundary to handle function.
     * @param value Value which determines the function.
     */
    void handleBoundary(Boundaries boundary, boundary_type& value);
public:

    /**
     * Constructor for BoundaryHandler
     * @param boundaries contains the boundary conditions for each side
     * @param domainSize Size of domain.
     * @param dimensions Dimensions of cell grid.
     */
    BoundaryHandler(boundaries_type boundaries, std::array<double, 3> domainSize,
                    std::array<int, 3> dimensions,
                    std::map<std::array<double, 2>, double> *mixedEpsilon, std::map<std::array<double, 2>, double> *mixedSigma);
    /**
     * Iterate cells at boundary b and apply function f.
     * @param b Boundary to iterate in.
     * @param f Function to be applied.
     */
    void iterateCellsAtBoundary(
            Boundaries b,
            const std::function<void(LinkedCell&, std::array<int,3> pos)>& f);

    /**
     * Handles all boundary conditions for current lcc configuration.
     */
    void handle(std::vector<LinkedCell>* cells);

    /**
     * Iterate particles at boundary b and apply function f.
     * @param b Boundary to iterate in.
     * @param f Function to be applied.
     */
    void iterateParticlesAtBoundary(Boundaries b, const std::function<void(Particle&)>& f);

    /**
     * Adds neighbours for periodic boundaries.
     * @param cells
     */
    void addPeriodicNeighbours(std::vector<LinkedCell>* cells);
};
