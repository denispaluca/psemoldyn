//
// Created by mira on 24.11.20.
//

#include <utils/XSDMapper.h>
#include "ParticleGenerator.h"
#include "deprecated/FileReader.h"

ParticleGenerator::ParticleGenerator(particle_data &data) : data(data) {
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

void ParticleGenerator::reserve(){
    std::size_t nrParticles = data.particles().particle().size();
    cuboids = std::vector<Cuboid>(data.cuboids().cuboid().size());
    for(auto c : data.cuboids().cuboid()){
        auto cube = mapCuboid(c);
        nrParticles += cube.getNrPartilces();
        cuboids.emplace_back(cube);
    }

    //TODO for spheres

    particles.reserve(nrParticles);
}

void ParticleGenerator::generate() {
    this->reserve();
    for(auto p: data.particles().particle()){
        auto particle = mapParticle(p);
        particles.push(particle);
    }
    for(auto c: cuboids){
        c.generate(particles);
    }

    //TODO for spheres
}