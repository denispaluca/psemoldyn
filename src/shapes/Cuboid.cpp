//
// Created by mira on 24.11.20.
//

#include "Cuboid.h"
#include "utils/MaxwellBoltzmannDistribution.h"
#include <sstream>
#include "utils/ArrayUtils.h"
#include <utils/ForceUtils.h>

Cuboid::Cuboid() {
    this->position = {0.0,0.0,0.0};
    this->size = {10, 10, 10};
    this->distance = 1;
    this->mass = 1;
    this->initialV = {0.0, 0.0, 0.0};
    this->isMembrane = false;
    //TODO: defaultvals for eps/sigma
}

Cuboid::Cuboid(std::array<double, 3> position, std::array<int, 3> particleNumbers, double distance, double mass,
               std::array<double, 3> initialV, double epsilon, double sigma, bool isMembrane, double r0, double k) {
    this->position = position;
    this->size = particleNumbers;
    this->distance = distance;
    this->mass = mass;
    this->initialV = initialV;
    this->epsilon = epsilon;
    this->sigma = sigma;
    this->isMembrane = isMembrane;
    this->r0 = r0;
    this->km = k;
}

Cuboid::Cuboid(std::array<double, 3> position, std::array<int, 3> particleNumbers, double distance, double mass,
               std::array<double, 3> initialV, double epsilon, double sigma, bool fixed) {
    this->position = position;
    this->size = particleNumbers;
    this->distance = distance;
    this->mass = mass;
    this->initialV = initialV;
    this->epsilon = epsilon;
    this->sigma = sigma;
    this->fixed = fixed;
}

void Cuboid::generate(ParticleContainer &particles) {
    std::array<double, 3> newPosition = {0., 0., 0.};

    int length = particles.size();

    int uid = 0;

    for(int i = 0; i < size[0]; i++){
        newPosition[0] = position[0] + i*distance; //xpos
        for(int j = 0; j < size[1]; j++){
            newPosition[1] = position[1] + j*distance; //ypos
            for(int k = 0; k < size[2]; k++){
                newPosition[2] =  position[2] + k*distance; //zpos
<<<<<<< HEAD
                Particle newParticle = Particle(newPosition, initialV, mass, epsilon, sigma, r0, km);
                newParticle.uid = uid++;
                newParticle.debug = 0;
=======
                //Particle newParticle = Particle(newPosition, initialV, mass, epsilon, sigma);
                Particle newParticle = Particle(newPosition, initialV, mass, epsilon, sigma, fixed);
>>>>>>> dev

                particles.push(newParticle);
            }
        }
    }
    if (isMembrane) {
        setNeighbours(particles.getParticles(), length, size[0]*size[1], size[0]);
    }
    return;
}

bool Cuboid::operator==(Cuboid &other) {
    return (position == other.position) and (size == other.size)
        and (distance == other.distance) and (mass == other.mass)
        and (epsilon == other.epsilon) and (sigma == other.sigma);
}

std::string Cuboid::toString() {
    std::stringstream stream;
    stream << "Cuboid: x:" << position << " size: " << size << " distance: " << distance
           << " mass: " << mass << " initialV: " << initialV << " epsilon: " << epsilon << " sigma: " << sigma;
    return stream.str();
}

std::array<int,3> Cuboid::getSize() {
    return size;
}

std::size_t Cuboid::getNrParticles() {
    return size[0] * size[1] * size[2];
}
