//
// Created by mira on 08.12.20.
//

#include "LinkedCellContainer.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <utils/ForceUtils.h>

LinkedCellContainer::LinkedCellContainer() {
    domain_size = {0.0, 0.0, 0.0};
    domain_pos = {0.0, 0.0, 0.0};
    cutoff_radius = 0.0;
    cells = std::vector<LinkedCell>();
    domainCells = std::vector<LinkedCell>();
    inner = std::vector<LinkedCell>();
    boundary = std::vector<LinkedCell>();
    halo = std::vector<LinkedCell>();
}

LinkedCellContainer::LinkedCellContainer(std::array<double, 3> domain_size,
                                         std::array<double, 3> domain_pos, double cutoff_radius, ParticleContainer &particles) {
    this->domain_size = domain_size;
    this->domain_pos = domain_pos;
    this->cutoff_radius = cutoff_radius;

    int cellsX = std::ceil(domain_size[0] / cutoff_radius);
    int cellsY = std::ceil(domain_size[1] / cutoff_radius);
    int cellsZ = std::ceil(domain_size[2] / cutoff_radius);

    cells = std::vector<LinkedCell>();
    inner = std::vector<LinkedCell>();
    boundary = std::vector<LinkedCell>();
    halo = std::vector<LinkedCell>();

    for(int i = -1; i <= cellsX; i++) {
        for(int j = -1; j <= cellsY; j++) {
            for(int k = -1; k <= cellsZ; k++) {
                std::array<double, 3> cellPos = {domain_pos[0] + i * cutoff_radius,
                                                 domain_pos[1] + j * cutoff_radius,
                                                 domain_pos[2] + k * cutoff_radius};

                // constructor of LinkedCell checks if particles belong to cell -> TODO: more efficient way?
                LinkedCell cell = LinkedCell(cellPos, cutoff_radius, particles);

                if(i == -1 || i == cellsX || j == -1 || j == cellsY || k == -1 || k == cellsZ) {
                    // cell is halo cell
                    halo.emplace_back(cell);
                } else if(i == 0 || i == cellsX - 1 || j == 0 || j == cellsY - 1 || k == 0 || k == cellsZ - 1) {
                    // cell is boundary cell
                    boundary.emplace_back(cell);
                    domainCells.emplace_back(cell);
                } else {
                    //cell is inner cell
                    inner.emplace_back(cell);
                    domainCells.emplace_back(cell);
                }

                cells.emplace_back(cell);
            }
        }
    }
}


const std::array<double, 3> &LinkedCellContainer::getDomainSize() const {
    return domain_size;
}

const std::array<double, 3> &LinkedCellContainer::getDomainPos() const {
    return domain_pos;
}

double LinkedCellContainer::getCutoffRadius() const {
    return cutoff_radius;
}

const std::vector<LinkedCell> &LinkedCellContainer::getCells() const {
    return cells;
}

const std::vector<LinkedCell> &LinkedCellContainer::getInner() const {
    return inner;
}

const std::vector<LinkedCell> &LinkedCellContainer::getBoundary() const {
    return boundary;
}

const std::vector<LinkedCell> &LinkedCellContainer::getHalo() const {
    return halo;
}

void LinkedCellContainer::linkedCellForceCalc() {
    for (auto i = domainCells.begin(); i != domainCells.end(); ++i) {
        // calculate forces between particles of one cell
        i->getParticles().iteratePairs(calculateLennardJones);

        // then calculate forces between particles of cell + neighbors
        for (auto j = i+1; j != domainCells.end(); ++j) {
            if(i->isNeighbor(*j)) {
                for (auto &pi : i->getParticles().getParticles()) {
                    for (auto &pj : j->getParticles().getParticles()) {
                        calculateLennardJones(pi, pj);
                    }
                }
            }
        }
    }
}

void LinkedCellContainer::deleteHaloParticles() {
   for(auto &i : halo) {
       i.setParticles(ParticleContainer());
   }
}
