//
// Created by mira on 08.12.20.
//

#include "LinkedCell.h"
#include <utils/MaxwellBoltzmannDistribution.h>
#include <algorithm>


LinkedCell::LinkedCell() {
    particles = std::vector<Particle*>();
    neighbors = std::vector<LinkedCell*>();
}

LinkedCell::LinkedCell(int index) {
    this->index = index;
    particles = std::vector<Particle*>();
    //neighbors are set in constructor of LinkedCellContainer
    neighbors = std::vector<LinkedCell*>();
}

std::vector<LinkedCell*> LinkedCell::getNeighbors() {
    return neighbors;
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
