//
// Created by mira on 24.11.20.
//

#include "Cuboid.h"
#include "utils/MaxwellBoltzmannDistribution.h"

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
    //int particleNumber = size[0] * size[1] * size[2];
    //particles.getParticles().reserve(particleNumber); // TODO: allocate space?

    // TODO: better way of generating Particles?
    for(int i = 0; i < size[0]; i++){
        for(int j = 0; j < size[1]; j++){
            for(int k = 0; k < size[2]; k++){
                std::array<double, 3> newPosition = {position[0] + i*distance, position[1] + j*distance, position[2] + k*distance};
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
