//
// Created by mira on 08.12.20.
//

#ifndef PSEMOLDYN_GROUPB_LINKEDCELLCONTAINER_H
#define PSEMOLDYN_GROUPB_LINKEDCELLCONTAINER_H

#include "LinkedCell.h"

class LinkedCellContainer {
private:
    /**
     * The size of the domain of the cells (inner + boundary)
     */
    std::array<double, 3> domain_size;

    /**
     * The position of the domain
     */
    std::array<double, 3> domain_pos; // TODO: do we need this?

    /**
     * THe cutoff-radius
     */
    double cutoff_radius;

    /**
     * A vector containing all cells
     */
    std::vector<LinkedCell> cells;

    /**
     * A vector containing all cells within the domain (inner + boundary)
     */
    std::vector<LinkedCell> domainCells;

    /**
     * A vector containing only the inner cells
     */
    std::vector<LinkedCell> inner;

    /**
     * A vector containing only the boundary cells
     */
    std::vector<LinkedCell> boundary;

    /**
     * A vector containing only the halo cells
     */
    std::vector<LinkedCell> halo;

    std::vector<LinkedCell> nonEmpty;

public:

    /**
     * Default constructor
     */
    LinkedCellContainer();

    /**
     * Constructor for a LinkedCellContainer, creates cells automatically + assigns correct particles
     * @param domain_size the domain size
     * @param domain_pos the position of the domain
     * @param cutoff_radius the cutoff radius
     * @param particles the particles
     */
    LinkedCellContainer(std::array<double, 3> domain_size, std::array<double, 3> domain_pos, double cutoff_radius, ParticleContainer &particles);

    /**
     * Getter for the domain size
     * @return the domain size
     */
    const std::array<double, 3> &getDomainSize() const;

    /**
     * Getter for the domain position
     * @return the domain position
     */
    const std::array<double, 3> &getDomainPos() const;

    /**
     * Getter for the cutoff radius
     * @return the cutoff radius
     */
    double getCutoffRadius() const;

    /**
     * Getter for the vector of cells
     * @return the vector of cells
     */
    const std::vector<LinkedCell> &getCells() const;

    /**
     * Getter for the vector of inner cells
     * @return the vector of inner cells
     */
    const std::vector<LinkedCell> &getInner() const;

    /**
     * Getter for the vector of boundary cells
     * @return the vector of boundary cells
     */
    const std::vector<LinkedCell> &getBoundary() const;

    /**
     * Getter for the vector of halo cells
     * @return the vector of halo cells
     */
    const std::vector<LinkedCell> &getHalo() const;

    /**
     * Calculates the forces between the particles using the Linked-Cell-Algorithm.
     */
    void linkedCellForceCalc();

    void updateCells();

    void calculateIteration();

    /**
     * Deletes all the particles located in halo cells
     */
    void deleteHaloParticles();

};


#endif //PSEMOLDYN_GROUPB_LINKEDCELLCONTAINER_H
