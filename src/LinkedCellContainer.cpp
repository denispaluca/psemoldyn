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
    cutoff_radius = 0.0;
    cells = std::vector<LinkedCell>();
}

LinkedCellContainer::LinkedCellContainer(std::array<double, 3> domain_size, double cutoff_radius,
                                         ParticleContainer &particles) {
    this->domain_size = domain_size;
    this->cutoff_radius = cutoff_radius;
    this->particles = particles;
    for(int i = 0; i < 3; i++)
        dimensions[i] = std::ceil(domain_size[i] / cutoff_radius);

    cells = std::vector<LinkedCell>();
    int nrCells = dimensions[0]*dimensions[1]*dimensions[2];
    cells.reserve(nrCells);
    for(int i = 0; i < nrCells; i++){
        auto pos = indexToPos(i);
        std::array<double, 3> cellPos = {pos[0] * cutoff_radius,
                                        pos[1] * cutoff_radius,
                                        pos[2] * cutoff_radius};
        cells.emplace_back(LinkedCell(cellPos, cutoff_radius, i));
    }

    this->particles.iterate([&](Particle& p){
        assignParticle(p);
    });

    LOG4CXX_INFO(linkedCellContainerLogger, "Starting neighbor calculation");

    int neighborIndex = 0;
    for(int i = 0; i < cells.size(); i++) {
        for(int j = -1; j <= 1; j++) {
            for(int k = -1; k <= 1; k++) {
                for(int l = -1; l <= 1; l++) {

                    neighborIndex = i + j * dimensions[0] + k * dimensions[1] + l;

                    if(neighborIndex != i && neighborIndex >= 0 && neighborIndex < cells.size()) {
                        cells.at(i).addNeighbor(&cells.at(neighborIndex));
                    }

                }
            }
        }
    }

    LOG4CXX_INFO(linkedCellContainerLogger, "Ended neighbor calculation");
}

void LinkedCellContainer::iterate(std::function<void(Particle &)> f) {
    particles.iterate(f);
}

void LinkedCellContainer::iteratePairs(std::function<void(Particle&, Particle&)> f) {
    for (auto cell : cells) {
        // calculate forces between particles of one cell

        //LOG4CXX_INFO(linkedCellContainerLogger, "INNER START");
        cell.iteratePairs(f);
        //LOG4CXX_INFO(linkedCellContainerLogger, "INNER END");

        // then calculate forces between particles of cell + neighbors
        //LOG4CXX_INFO(linkedCellContainerLogger, "OUT START");
        for (auto j : cell.getNeighbors()) {
//            std::array<double, 3> xDiff = j->getPosition();
//            xDiff = {xDiff[0] - cell.getPosition()[0],
//                     xDiff[1] - cell.getPosition()[1],
//                     xDiff[2] - cell.getPosition()[2]};

//            if(xDiff[0] > 0 || (xDiff[0] == 0 && xDiff[1] > 0) || (xDiff[0] == 0 && xDiff[1] == 0 && xDiff[2] > 0)) {
            if(cell.getIndex() < j->getIndex()){
                for(auto pi : cell.getParticles()){
                    for(auto pj : j->getParticles()){
                        f(*pi,*pj);
                    }
                }
            }
        }
        //LOG4CXX_INFO(linkedCellContainerLogger, "OUT START");
    }
}

void LinkedCellContainer::calculateIteration() {
    //calculate new positions
    iterate([](Particle &p) {
            p.calculateX();
            p.saveOldF();
    });

    // calculate new f
    iteratePairs(calculateLennardJones);

    for(auto& c:cells){
        c.removeParticles();
    }

    // calculate new v
    iterate([&](Particle &p) {
        p.calculateV();
        assignParticle(p);
    });
//    for(auto c : cells) {
//        c.iterate([](Particle &p) {
//            p.calculateV();
//        });
//        c.removeParticles();
//    }
}

int LinkedCellContainer::getIndex(std::array<int, 3> pos) {
    return pos[0] + (pos[1]+ pos[2]*dimensions[1])*dimensions[0];
}

void LinkedCellContainer::assignParticle(Particle &p) {
    std::array<int,3> x{};
    for(int i = 0; i<3;i++)
        x[i] = (int)std::floor(p.getX()[i]/cutoff_radius);

    int index = getIndex(x);
    if(index < 0 || index >= particles.getParticles().size()){
        //LOG4CXX_INFO(linkedCellContainerLogger, "Particle outside of domain");
        return;
    }

    cells.at(index).addParticle(&p);
}

std::array<int, 3> LinkedCellContainer::indexToPos(int i) {
    int z = i / (dimensions[0] * dimensions[1]);
    i -= (z * dimensions[0] * dimensions[1]);
    int y = i / dimensions[0];
    int x = i % dimensions[0];
    return { x, y, z };
}
