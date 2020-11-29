//
// Created by mira on 24.11.20.
//

#include "ParticleGenerator.h"
#include "FileReader.h"

ParticleGenerator::ParticleGenerator() {
    cuboids = std::vector<Cuboid>();
    particles = ParticleContainer();
}

ParticleGenerator::ParticleGenerator(char *filename) {
    cuboids = std::vector<Cuboid>();
    FileReader fileReader;
    fileReader.readCuboids(cuboids, filename);

    particles = ParticleContainer();
    for(auto &c : cuboids)
        c.generate(particles);
}

std::vector<Cuboid> ParticleGenerator::getCuboids() {
    return cuboids;
}

ParticleContainer ParticleGenerator::getParticles() {
    return particles;
}

void ParticleGenerator::addCuboid(Cuboid c) {
    cuboids.emplace_back(c);
    c.generate(particles);
}
