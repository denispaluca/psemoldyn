//
// Created by mira on 24.11.20.
//

#include <utils/XSDMapper.h>
#include "ParticleGenerator.h"
#include "deprecated/FileReader.h"

ParticleGenerator::ParticleGenerator() {
    cuboids = std::vector<Cuboid>();
    particles = ParticleContainer();
}

ParticleGenerator::ParticleGenerator(particle_data &data) {
    cuboids = std::vector<Cuboid>();
    particles = ParticleContainer();
    for(auto p : data.particles().particle()){
        auto particle = mapParticle(p);
        particles.push(particle);
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

std::vector<Cuboid> ParticleGenerator::getCuboids() {
    return cuboids;
}

ParticleContainer& ParticleGenerator::getParticles() {
    return particles;
}

void ParticleGenerator::addCuboid(Cuboid c) {
    cuboids.emplace_back(c);
    c.generate(particles);
}
