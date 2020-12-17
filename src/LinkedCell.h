//
// Created by mira on 08.12.20.
//

#pragma once

#include <functional>
#include "Particle.h"
#include <vector>

class LinkedCell {
private:
    int index;

    /**
     * The particles located in this cell.
     */
    std::vector<Particle*> particles;

    /**
     * The neighboring cells
     */
    std::vector<LinkedCell*> neighbors;

public:

    /**
     * Default constructor
     */
    LinkedCell();

    /**
     * Constructor for a cell
     * @param particles particles to add to the cell
     *
     * The constructor adds the particles by calling addParticles(..),
     * i.e. it is checked that the particles are actually locaed within the cell.
     */
    LinkedCell(int index);

    /**
     * Getter for the neighbors fields
     * @return a vector with the neighboring LinkedCells of this cell
     */
    std::vector<LinkedCell*> getNeighbors();

    void addNeighbor(LinkedCell* other);

    void removeParticles();

    void addParticle(Particle* p);

    void iteratePairs(std::function<void(Particle&, Particle&)> f);

    int getIndex();

    std::vector<Particle*>& getParticles();
};