//
// Created by mira on 08.12.20.
//

#ifndef PSEMOLDYN_GROUPB_LINKEDCELLCONTAINER_H
#define PSEMOLDYN_GROUPB_LINKEDCELLCONTAINER_H

#include "LinkedCell.h"
#include "ParticleContainer.h"

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
    LinkedCellContainer(std::array<double, 3> domain_size, double cutoff_radius, ParticleContainer &particles);


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


#endif //PSEMOLDYN_GROUPB_LINKEDCELLCONTAINER_H
