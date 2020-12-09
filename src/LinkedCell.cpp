//
// Created by mira on 08.12.20.
//

#include "LinkedCell.h"


LinkedCell::LinkedCell() {
    position = {0,0,0};
    cutoff = 1;
    particles = ParticleContainer();
}

LinkedCell::LinkedCell(std::array<double, 3> position, double cutoff, ParticleContainer &particles) {
    this->position = position;
    this->cutoff = cutoff;
    addParticles(particles);
}


std::array<double, 3> LinkedCell::getPosition() {
    return position;
}

double LinkedCell::getCutoffRadius() {
    return cutoff;
}

ParticleContainer LinkedCell::getParticles() {
    return particles;
}

void LinkedCell::setParticles(const ParticleContainer &particles) {
    LinkedCell::particles = particles;
}

bool LinkedCell::particleBelongs(Particle &p) {
    return (position[0] < p.getX()[0] && position[1] < p.getX()[1] && position[1] < p.getX()[1] &&
            p.getX()[0] < position[0] + cutoff  && p.getX()[1] < position[1] + cutoff && p.getX()[2] < position[2] + cutoff);
}

bool LinkedCell::isNeighbor(LinkedCell &other) {
    std::array<double, 3> diff = other.getPosition();
    diff[0] -= position[0];
    diff[1] -= position[1];
    diff[2] -= position[2];
    return (std::abs(diff[0]) == cutoff || std::abs(diff[1]) == cutoff || std::abs(diff[2]) == cutoff);
}

void LinkedCell::addParticles(ParticleContainer particles) {
    for (auto &p : particles.getParticles()) {  // TODO: change to use iterate function?
        if(particleBelongs(p)) particles.push(p);
    }
}
