//
// Created by mira on 24.11.20.
//

#include <utils/XSDMapper.h>
#include "ParticleGenerator.h"
#include "FileReader.h"

ParticleGenerator::ParticleGenerator() {
    cuboids = std::vector<Cuboid>();
    particles = ParticleContainer();
}

ParticleGenerator::ParticleGenerator(particle_data &data) {
    for(auto p : data.particles().particle()){
        particles.push(mapParticle(p));
    }

    for(auto c : data.cuboids().cuboid()){
        mapCuboid(c).generate(particles);
    }

    // TODO Task 4
    /*
     * for(auto c : data.spheres().sphere()){
            mapSphere(c).generate(particles);
        }
     */
}

ParticleGenerator::ParticleGenerator(const char *filename) {
    cuboids = std::vector<Cuboid>();
    FileReader fileReader;
    fileReader.readCuboids(cuboids, filename);

    particles = ParticleContainer();

    int numberOfParticles = 0;
    for(auto &c : cuboids){
        auto size = c.getSize();
        numberOfParticles += size[0] * size[1] * size[2];
    }

    particles.reserve(numberOfParticles);

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
