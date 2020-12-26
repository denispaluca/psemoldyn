//
// Created by mira on 08.12.20.
//

#pragma once

#include <xml/molsimInput.hxx>
#include "LinkedCell.h"
#include "particle/ParticleContainer.h"
#include "BoundaryHandler.h"

class LinkedCellContainer : public Container {
private:
    /**
     * The size of the domain of the cells (inner + boundary)
     */
    std::array<double, 3> domain_size{};

    /**
     * The number of cells per dimension.
     */
    std::array<int, 3> dimensions{};

    /**
     * THe cutoff-radius
     */
    double cutoff_radius;

    /**
     * A vector containing all cells
     */
    std::vector<LinkedCell> cells;

    /**
     * THe particles contained in this container
     */
    ParticleContainer particles;

    /**
     * A pointer to this LinkedCellContainer's BoundaryHandler
     */
    BoundaryHandler* boundaryHandler;

    /**
     * Deletes all particles outside of the container's domain
     */
    void clearOutflowParticles();

    /**
     * Finds and adds neighbors of LinkedCells.
     */
    void populateNeighbours();

public:
    LinkedCellContainer();
    /**
     * Constructor for a LinkedCellContainer, creates cells automatically + assigns correct particles
     * @param domain_size the domain size
     * @param domain_pos the position of the domain
     * @param cutoff_radius the cutoff radius
     * @param particles the particles
     */
    LinkedCellContainer(domain_type domain, ParticleContainer &particles);

    /**
    * Does one iteration step with the particles
    */
    void calculateIteration() override;

    /**
     * Adds goven Particle to correct LinkeCell.
     * @param p the Particle to be added
     * @return true if Particle was added, false if Particle is outside of domain
     */
    bool assignParticle(Particle& p);

    /**
     * Calculates index of the LinkedCell containing the given point in space
     * @param pos the coordinates
     * @return the index of the LinkedCell
     */
    int getIndex(std::array<int, 3> pos);

    /**
     * Iterate over all particles and apply function f
     * @param f Function applied to particles
     * @return
     */
    void iterate(std::function<void(Particle&)> f) override;

    /**
     * Iterate over all unique particle pairs and apply function f
     * @param f Function that is applied to pairs
     * @return
     */
    void iteratePairs(std::function<void(Particle&, Particle&)> f) override;

    /**
     * Calculates position of LinkedCell (lower front-left corner) from its index
     * @param i
     * @return
     */
    std::array<int,3> indexToPos(int i);

    /**
     * Calculates index of the LInkedCell the given particle belongs to
     * @param p
     * @return
     */
    int getIndexFromParticle(Particle& p);

    /**
     * The number of particles in this LinkedCellContainer
     * @return
     */
    std::size_t size() override;

    /**
     * Getter for vector of LinkedCells
     * @return the LinkedCells of this container
     */
    std::vector<LinkedCell>& getCells();

    /**
     * Getter for ParticleContainer
     * @return the ParticleContainer containing the Particles of this cell
     */
    ParticleContainer& getParticles();

    /**
     * Getter for cell grid dimensions.
     * @return Dimensions
     */
    std::array<int, 3>& getDimensions();

    /**
     * Getter for domain size.
     * @return Domain size
     */
    std::array<double, 3>& getDomainSize();

    BoundaryHandler* getBoundaryHandler();
};