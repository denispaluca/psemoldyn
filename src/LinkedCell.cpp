//
// Created by mira on 08.12.20.
//

#include "LinkedCell.h"
#include <utils/MaxwellBoltzmannDistribution.h>
#include <algorithm>


LinkedCell::LinkedCell() {
    position = {0,0,0};
    cutoff = 1;
    particles = std::vector<Particle*>();
    neighbors = std::vector<LinkedCell*>();
}

LinkedCell::LinkedCell(std::array<double, 3> position, double cutoff, int index) {
    this->position = position;
    this->cutoff = cutoff;
    this->index = index;
    this->particles = std::vector<Particle*>();

    //neighbors are set in constructor of LinkedCellContainer
    neighbors = std::vector<LinkedCell*>();
}


std::array<double, 3> LinkedCell::getPosition() {
    return position;
}

std::vector<LinkedCell*> LinkedCell::getNeighbors() {
    return neighbors;
}

bool LinkedCell::isNeighbor(LinkedCell* other) {
    std::array<double, 3> diff = other->getPosition();
    diff[0] -= position[0];
    diff[1] -= position[1];
    diff[2] -= position[2];
    return (std::abs(diff[0]) == cutoff || std::abs(diff[1]) == cutoff || std::abs(diff[2]) == cutoff);
}

void LinkedCell::removeParticles(){
    particles.clear();
}

void LinkedCell::addNeighbor(LinkedCell* other) {
    neighbors.emplace_back(other);
}

void LinkedCell::addParticle(Particle *p) {
    particles.emplace_back(p);
}

void LinkedCell::iterate(std::function<void(Particle&)> f) {
    for(auto particle : particles)
        f(*particle);
}

void LinkedCell::iteratePairs(std::function<void(Particle&, Particle&)> f) {
    for(auto i = particles.begin(); i != particles.end(); ++i)
        for(auto j = i + 1; j != particles.end(); ++j)
            f(**i,**j);
}

int LinkedCell::getIndex() {
    return index;
}

std::vector<Particle *> &LinkedCell::getParticles() {
    return particles;
}
