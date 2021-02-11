//
// Created by mira on 24.11.20.
//

#include <utils/XSDMapper.h>
#include "ParticleGenerator.h"
#include "utils/MaxwellBoltzmannDistribution.h"

ParticleGenerator::ParticleGenerator(particle_data &data, Thermostat* t = nullptr) : data(data) {
    thermostat = t;
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
    c.generate(particles);
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
        c.generate(particles);
    }
    for(auto c: particleSpheres){
        c.generate(particles, data.is3D());
    }

    applyBrownianMotion();
}

ParticleGenerator::ParticleGenerator() : data(0.1,true,cuboid_cluster(),particle_cluster(),sphere_cluster()) {
    cuboids = std::vector<Cuboid>();
    particles = ParticleContainer();
    particleSpheres = std::vector<ParticleSphere>();
    thermostat = nullptr;
}

void ParticleGenerator::applyBrownianMotion() {
    if(thermostat == nullptr || !thermostat->changeBrownian()) {
        auto meanv = data.meanv();
        auto dim = data.is3D() ? 3 : 2;
        particles.iterate([meanv,dim](Particle &p) {
            if (!p.fixed) MaxwellBoltzmannDistribution(p, meanv, dim);
        });
    } else
        thermostat->applyBrownian(particles);
}
