//
// Created by mira on 08.12.20.
//

#pragma once

#include <functional>
#include "particle/Particle.h"
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
    std::vector<LinkedCell*> &getNeighbors();

    /**
     * Adds given LinkedCell pointer to vector of neighbors.
     * @param other a pointer to the LinkedCell to be added
     */
    void addNeighbor(LinkedCell* other);

    /**
     * Deletes all Particles from this LinkedCell.
     */
    void removeParticles();

    /**
     * Adds given Particle pointer to vector of contained particles.
     * @param p a pointer to the Particle to be added
     */
    void addParticle(Particle* p);

    /**
     * Applies given function to all distinct particle pairs in this LinkedCell.
     * @param f the function t be applied.
     */
    void iteratePairs(std::function<void(Particle&, Particle&)> f);

    /**
     * The index of this LinkedCell (wrt the Container it belongs to)
     * @return the index
     */
    int getIndex();

    /**
     * Getter for the Particles vector.
     * @return
     */
    std::vector<Particle*>& getParticles();

    /**
     * Checks if c is in the neighbour vector of the current cell.
     * @param c Cell to be checked.
     * @return True if it is a neighbour.
     */
     bool isNeighbour(LinkedCell& c);
};