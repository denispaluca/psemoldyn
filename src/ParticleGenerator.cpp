//
// Created by mira on 24.11.20.
//

#include <utils/XSDMapper.h>
#include "ParticleGenerator.h"
#include "deprecated/FileReader.h"

ParticleGenerator::ParticleGenerator(particle_data &data) : data(data) {
    cuboids = std::vector<Cuboid>();
    particles = ParticleContainer();
    particleSpheres = std::vector<ParticleSphere>();
    generate();
}

std::vector<Cuboid> ParticleGenerator::getCuboids() {
    return cuboids;
}

std::vector<ParticleSphere> ParticleGenerator::getParticleSpheres() {
    return particleSpheres;
}

ParticleContainer& ParticleGenerator::getParticles() {
    return particles;
}

void ParticleGenerator::addCuboid(Cuboid c) {
    cuboids.emplace_back(c);
    c.generate(particles, data.is3D());
}

void ParticleGenerator::reserve(){
    std::size_t nrParticles = data.particles().particle().size();

    cuboids.reserve(data.cuboids().cuboid().size());
    for(auto c : data.cuboids().cuboid()){
        auto cube = mapCuboid(c);
        nrParticles += cube.getNrParticles();
        cuboids.emplace_back(cube);
    }

    particleSpheres.reserve(data.spheres().sphere().size());
    for(auto c : data.spheres().sphere()){
        auto sphere = mapParticleSphere(c);
        nrParticles += sphere.getNrParticles();
        particleSpheres.emplace_back(sphere);
    }

    particles.reserve(nrParticles);
}

void ParticleGenerator::generate() {
    reserve();
    for(auto p: data.particles().particle()){
        auto particle = mapParticle(p);
        particles.push(particle);
    }
    for(auto c: cuboids){
        c.generate(particles, data.is3D());
    }
    for(auto c: particleSpheres){
        c.generate(particles);
    }
}