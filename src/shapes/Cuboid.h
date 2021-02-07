//
// Created by mira on 24.11.20.
//
#pragma once

#include <array>
#include "particle/ParticleContainer.h"

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

    double epsilon;

    double sigma;

    bool isMembrane;

    double r0;

    double km;

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
     * @param epsilon epsilon of the particles
     * @param sigma sigma of the particles
     * @param membrane if cuboid is a membrane
     */
    Cuboid(std::array<double, 3> position, std::array<int, 3> size,
           double distance, double mass, std::array<double, 3> initalV,
           double epsilon, double sigma, bool membrane, double r0, double k);

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

    /**
     * Getter for the number of particles in cuboid
     * @return Number of particles in cuboid
     */
    std::size_t getNrParticles();

    /**
     * Store a membrane in 2d vector
     */
    //std::vector<std::vector<Particle>> membrane;
};