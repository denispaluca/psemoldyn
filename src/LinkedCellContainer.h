//
// Created by mira on 08.12.20.
//

#pragma once

#include <xml/molsimInput.hxx>
#include "LinkedCell.h"
#include "ParticleContainer.h"
#include "BoundaryHandler.h"

class LinkedCellContainer : public Container {
private:
    /**
     * The size of the domain of the cells (inner + boundary)
     */
    std::array<double, 3> domain_size{};

    std::array<int, 3> dimensions{};

    /**
     * THe cutoff-radius
     */
    double cutoff_radius;

    /**
     * A vector containing all cells
     */
    std::vector<LinkedCell> cells;

    std::vector<LinkedCell*> nonEmpty;

    ParticleContainer particles;

    BoundaryHandler* boundaryHandler;

    void clearOutflowParticles();

    void populateNeighbours();

public:
    /**
     * Constructor for a LinkedCellContainer, creates cells automatically + assigns correct particles
     * @param domain_size the domain size
     * @param domain_pos the position of the domain
     * @param cutoff_radius the cutoff radius
     * @param particles the particles
     */
    LinkedCellContainer(domain_type domain, ParticleContainer &particles);


    void calculateIteration() override;

    bool assignParticle(Particle& p);

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

    std::array<int,3> indexToPos(int i);

    int getIndexFromParticle(Particle& p);

    std::size_t size() override;
};