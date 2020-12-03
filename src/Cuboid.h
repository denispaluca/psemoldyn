//
// Created by mira on 24.11.20.
//
#pragma once

#define MEAN_BROWNIAN 0.1

#include <array>
#include "ParticleContainer.h"

class Cuboid{

private:
    /**
     * Position of cuboid (lower left corner)
     */
    std::array<double, 3> position{};

    /**
     * # of particles for each dimension
     */
    std::array<int, 3> size{};

    /**
     * Mesh width
     */
    double distance;

    /**
     * Mass of particles
     */
    double mass;

    /**
     * Initial velocity of particles
     */
    std::array<double, 3> initialV{};

    /**
     * Mean value of velocity of Brownian Motion
     */
    double meanV;
public:
    /**
     * Default constructor
     * @return
     */
    Cuboid();

    /**
     * Constructs Cuboid with given parameters
     * @param position coordinates of the lower left front-side corner
     * @param size size of the Cuboid, given in number of particles per dimension
     * @param distance distance between particles/mesh width
     * @param mass mass of one particle
     * @param initalV initial velocity of the particles
     * @param meanV mean-value of velocity of Brownian Motion (will be discarded, we use a hard-coded value instead)
     */
    Cuboid(std::array<double, 3> position, std::array<int, 3> size,
           double distance, double mass, std::array<double, 3> initalV, double meanV);

        /**
     * Operator that compares all attributes of
     * this cuboid with another.
     * @param other Cuboid to be compared to.
     * @return TRUE when all attributes are the same
     */
    bool operator==(Cuboid &other);

    /**
   * Represent this cuboid in string format.
   * @return String representation of this particle.
   * @param
   */
    std::string toString();

    /**
     * Generates the particles in the cuboid and adds them into given ParticleContainer
     * @param p the ParticleContainer in which the generated Particles shall be stored
     */
    void generate(ParticleContainer &p);

    /**
     * Getter for the size of cuboid.
     * @return Size of cuboid
     */
    std::array<int,3>  getSize();
};