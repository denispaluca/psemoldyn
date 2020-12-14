//
// Created by mira on 08.12.20.
//

#include "LinkedCell.h"
#include <utils/MaxwellBoltzmannDistribution.h>
#include <algorithm>


LinkedCell::LinkedCell() {
    position = {0,0,0};
    cutoff = 1;
    particles = ParticleContainer();
    neighbors = std::vector<LinkedCell>();
}

LinkedCell::LinkedCell(std::array<double, 3> position, double cutoff, ParticleContainer &particles) {
    this->position = position;
    this->cutoff = cutoff;
    this->particles = ParticleContainer();
    
    //addParticles(particles);
    moveParticlesFrom(particles);

    //neighbors are set in constructor of LinkedCellContainer
    neighbors = std::vector<LinkedCell>();
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

std::vector<LinkedCell> LinkedCell::getNeighbors() {
    return neighbors;
}

void LinkedCell::setParticles(const ParticleContainer &particles) {
    this->particles = particles;
}

bool LinkedCell::particleBelongs(Particle &p) {
    return (position[0] <= p.getX()[0] && position[1] <= p.getX()[1] && position[1] <= p.getX()[1] &&
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
        if(particleBelongs(p)) this->particles.push(p);
    }
}

void LinkedCell::pullParticles(LinkedCell &other) {
    if(isNeighbor(other)) {
        moveParticlesFrom(other.getParticles());
    }
}

void LinkedCell::moveParticlesFrom(ParticleContainer particles){
    int toDelete = 0;
    ParticleContainer addHere = ParticleContainer();
    std::vector<Particle> p = particles.getParticles();

    for(int i = 0; i < p.size()-toDelete; i++) {
        if(this->particleBelongs(p.at(i))) {
            addHere.push(p.at(i));
            iter_swap(p.begin() + i, p.begin() + p.size() - toDelete - 1);
            toDelete++;
            i--;
        }
    }

    addParticles(addHere);

    p.erase(p.begin() + p.size() - toDelete, p.end());
}


void LinkedCell::addNeighbor(LinkedCell &other) {
    neighbors.emplace_back(other);
}
