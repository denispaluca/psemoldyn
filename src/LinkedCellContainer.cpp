//
// Created by mira on 08.12.20.
//

#include "LinkedCellContainer.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <utils/ForceUtils.h>

#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
using namespace log4cxx;
using namespace log4cxx::helpers;

//static logger variable linkedCellContainerLogger
log4cxx::LoggerPtr linkedCellContainerLogger(log4cxx::Logger::getLogger("linkedcellcont"));

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
    domainCells = std::vector<LinkedCell>();

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

                LOG4CXX_INFO(linkedCellContainerLogger, "created Cell");
            }
        }
    }

    LOG4CXX_INFO(linkedCellContainerLogger, "Starting neighbor calculation");

    int neighborIndex = 0;
    for(int i = 0; i < cells.size(); i++) {
        for(int j = -1; j <= 1; j++) {
            for(int k = -1; k <= 1; k++) {
                for(int l = -1; l <= 1; l++) {

                    neighborIndex = i + j * cellsX + k * cellsY + l;

                    if(neighborIndex != i && neighborIndex >= 0 && neighborIndex < cells.size()) {
                        cells.at(i).addNeighbor(cells.at(neighborIndex));
                    }

                }
            }
        }
    }

    LOG4CXX_INFO(linkedCellContainerLogger, "Ended neighbor calculation");
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
        for (auto &j : i->getNeighbors()) {
            std::array<double, 3> xDiff = j.getPosition();
            xDiff = {xDiff[0] - i->getPosition()[0], xDiff[1] - i->getPosition()[1], xDiff[2] - i->getPosition()[2]};
            
            if(xDiff[0] > 0 || (xDiff[0] == 0 && xDiff[1] > 0) || (xDiff[0] == 0 && xDiff[1] == 0 && xDiff[2] > 0)) {
                for (auto &pi : i->getParticles().getParticles()) {
                    for (auto &pj : j.getParticles().getParticles()) {
                        calculateLennardJones(pi, pj);
                    }
                }
            }
        }
    }
}

void LinkedCellContainer::updateCells() {
    for(auto &i : cells) {
        for (auto &j : i.getNeighbors())
            i.pullParticles(j);
    }
}

void LinkedCellContainer::calculateIteration() {
    //calculate new positions
    for (auto &c : cells) {
        c.getParticles().iterate([](Particle &p) {
            p.calculateX();
            p.saveOldF();
        });
    }

    //redistribute particles
    updateCells();

    // calculate new f
    linkedCellForceCalc();

    // calculate new v
    for(auto &c : cells) {
        c.getParticles().iterate([](Particle &p) {
            p.calculateV();
        });
    }
}

void LinkedCellContainer::deleteHaloParticles() {
   for(auto &i : halo) {
       i.setParticles(ParticleContainer());
   }
}
