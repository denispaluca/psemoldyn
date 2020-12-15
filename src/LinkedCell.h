//
// Created by mira on 08.12.20.
//

#ifndef PSEMOLDYN_GROUPB_LINKEDCELL_H
#define PSEMOLDYN_GROUPB_LINKEDCELL_H

#include "ParticleContainer.h"

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

    /**
     * The particles located in this cell.
     */
    ParticleContainer particles;

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
    LinkedCell(std::array<double, 3> position, double cutoff, ParticleContainer &particles);

    /**
     * Getter for the position field
     * @return the position
     */
    std::array<double, 3> getPosition();

    /**
     * Getter for the cutoff radius field
     * @return the cutoff radius
     */
    double getCutoffRadius();

    /**
     * Getter for the particles field
     * @return a ParticleContainer with the particles located in this cell
     */
    ParticleContainer getParticles();

    /**
     * Getter for the neighbors fiels
     * @return a vector with the neighboring LinkedCells of this cell
     */
    std::vector<LinkedCell*> getNeighbors();

    /**
     * Setter for particles
     * @param particles a ParticleContainer to which the particles field will be set
     */
    void setParticles(const ParticleContainer &particles);

    /**
     * Checks if another cell is a direct neighbor of the current cell.
     * @param other the other cell
     * @return true if the cells are neighbors, false otherwise
     */
    bool isNeighbor(LinkedCell* other);

    /**
     * Checks if the given particle is located within the bounds of this cell.
     * @param p the particle in question
     * @return true if the particle is located within this cell, false otherwise
     */
    bool particleBelongs(Particle &p);

    /**
     * Adds particles from given ParticleContainer to the particles stored in this cell
     * if they belong.
     * @param particles the ParticleContainer with particles to be added
     */
    void addParticles(ParticleContainer particles);

    void addNeighbor(LinkedCell* other);

    void moveParticlesFrom(ParticleContainer particles);

    void removeParticles();

};


#endif //PSEMOLDYN_GROUPB_LINKEDCELL_H
