//
// Created by mira on 24.11.20.
//

#include "Cuboid.h"
#include "utils/MaxwellBoltzmannDistribution.h"
#include <sstream>
#include "utils/ArrayUtils.h"

Cuboid::Cuboid() {
    this->position = {0.0,0.0,0.0};
    this->size = {10, 10, 10};
    this->distance = 1;
    this->mass = 1;
    this->initialV = {0.0, 0.0, 0.0};
    this->meanV = MEAN_BROWNIAN;
}

Cuboid::Cuboid(std::array<double, 3> position, std::array<int, 3> particleNumbers, double distance, double mass,
               std::array<double, 3> initialV, double meanV) {
    this->position = position;
    this->size = particleNumbers;
    this->distance = distance;
    this->mass = mass;
    this->initialV = initialV;
    this->meanV = MEAN_BROWNIAN;
}

void Cuboid::generate(ParticleContainer &particles) {
    std::array<double, 3> newPosition = {0., 0., 0.};

    for(int i = 0; i < size[0]; i++){
        newPosition[0] = position[0] + i*distance; //xpos
        for(int j = 0; j < size[1]; j++){
            newPosition[1] = position[1] + j*distance; //ypos
            for(int k = 0; k < size[2]; k++){
                newPosition[2] =  position[2] + k*distance; //zpos
                Particle newParticle = Particle(newPosition, initialV, mass);

                MaxwellBoltzmannDistribution(newParticle, meanV, 3);

                particles.push(newParticle);
            }
        }
    }
}

bool Cuboid::operator==(Cuboid &other) {
    return (position == other.position) and (size == other.size) and (distance == other.distance) and (mass == other.mass) and (meanV == other.meanV);
}

std::string Cuboid::toString() {
    std::stringstream stream;
    stream << "Cuboid: x:" << position << " size: " << size << " distance: " << distance
           << " mass: " << mass << " initialV: " << initialV;
    return stream.str();
}

std::array<int,3> Cuboid::getSize() {
    return size;
}

std::size_t Cuboid::getNrParticles() {
    return size[0] * size[1] * size[2];
}
