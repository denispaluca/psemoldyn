//
// Created by mira on 08.12.20.
//

#ifndef PSEMOLDYN_GROUPB_LINKEDCELL_H
#define PSEMOLDYN_GROUPB_LINKEDCELL_H

#include <functional>
#include "Particle.h"
#include <vector>

class LinkedCell {
private:
    /**
     * Coordinates of the lower front-left corner of ths cell.
     */
    std::array<double, 3> position;

    /**
     * the cutoff radius
     */
    double cutoff;

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
     * @param position coordinates of lower front-left corner
     * @param cutoff the cutoff radius
     * @param particles particles to add to the cell
     *
     * The constructor adds the particles by calling addParticles(..),
     * i.e. it is checked that the particles are actually locaed within the cell.
     */
    LinkedCell(std::array<double, 3> position, double cutoff, int index);

    /**
     * Getter for the position field
     * @return the position
     */
    std::array<double, 3> getPosition();

    /**
     * Getter for the neighbors fields
     * @return a vector with the neighboring LinkedCells of this cell
     */
    std::vector<LinkedCell*> getNeighbors();

    /**
     * Checks if another cell is a direct neighbor of the current cell.
     * @param other the other cell
     * @return true if the cells are neighbors, false otherwise
     */
    bool isNeighbor(LinkedCell* other);

    void addNeighbor(LinkedCell* other);

    void removeParticles();

    void addParticle(Particle* p);

    void iterate(std::function<void(Particle&)> f);

    void iteratePairs(std::function<void(Particle&, Particle&)> f);

    int getIndex();

    std::vector<Particle*>& getParticles();

};


#endif //PSEMOLDYN_GROUPB_LINKEDCELL_H
