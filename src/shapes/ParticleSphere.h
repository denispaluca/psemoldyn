//
// Created by Jonas on 17.12.20.
//

#pragma once

#include <array>
#include <particle/ParticleContainer.h>
//#include "ParticleSphere.cpp"

class ParticleSphere {

private:
    /**
     * Position of sphere (center)
     */
    std::array<double, 3> position{};

    /**
     * Initial velocity of particles
    */
    std::array<double, 3> initialV{};

    /**
     * # of particles along the radius
     */
    int radius;

    /**
     * Mesh width
     */
    double distance;

    /**
     * Mass of particles
     */
    double mass;

    /**
     * Mean value of velocity of Brownian Motion
     */
    double meanV;
public:
    /**
     * Default constructor
     * @return
     */
    ParticleSphere();

    /**
     * Constructs Sphere with given parameters
     * @param Position of sphere (center)
     * @param # of particles along the radius
     * @param distance distance between particles/mesh width
     * @param mass mass of one particle
     * @param initalV initial velocity of the particles
     */
    ParticleSphere(
            std::array<double, 3> position,
            std::array<double, 3> initalV,
            int radius,
            double distance,
            double mass,
            double meanV);

    /**
 * Operator that compares all attributes of
 * this Sphere with another.
 * @param other Sphere to be compared to.
 * @return TRUE when all attributes are the same
 */
    bool operator==(ParticleSphere &other);

    /**
   * Represent this Sphere in string format.
   * @return String representation of this Sphere.
   * @param
   */
    std::string toString();

    /**
     * Generates the particles in the cuboid and adds them into given ParticleContainer
     * @param p the ParticleContainer in which the generated Particles shall be stored
     */
    void generate(ParticleContainer &p);

    /**
     * Getter for the radius of Sphere.
     * @return Size of sphere
     */
    int getRadius();

    /**
     * Getter for the number of particles in Sphere
     * @return Number of particles in Sphere
     */
    std::size_t getNrParticles();
};