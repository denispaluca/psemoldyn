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
#include <xml/molsimInput.hxx>
#include <utils/XSDMapper.h>

using namespace log4cxx;
using namespace log4cxx::helpers;

//static logger variable linkedCellContainerLogger
log4cxx::LoggerPtr linkedCellContainerLogger(log4cxx::Logger::getLogger("linkedcellcont"));

LinkedCellContainer::LinkedCellContainer(domain_type domain,
                                         ParticleContainer &particles){
    this->domain_size = mapDoubleVec(domain.domain_size());
    this->cutoff_radius = std::abs(domain.cutoff_radius());
    this->particles = particles;
    gravity = domain.gravity();

    for(int i = 0; i < 3; i++)
        dimensions[i] = std::ceil(domain_size[i] / cutoff_radius);

    cells = std::vector<LinkedCell>();
    int nrCells = dimensions[0]*dimensions[1]*dimensions[2];
    cells.reserve(nrCells);
    for(int i = 0; i < nrCells; i++){
        cells.emplace_back(LinkedCell(i));
    }

    this->particles.iterate([&](Particle& p){
        assignParticle(p);
    });

    boundaryHandler = new BoundaryHandler(domain.boundary(), domain_size, dimensions);

    LOG4CXX_INFO(linkedCellContainerLogger, "Starting neighbor calculation");

    populateNeighbours();

    LOG4CXX_INFO(linkedCellContainerLogger, "Ended neighbor calculation");
}

void LinkedCellContainer::iterate(std::function<void(Particle &)> f) {
    particles.iterate(f);
}

void LinkedCellContainer::iteratePairs(std::function<void(Particle&, Particle&)> f) {
    for (auto& cell : cells) {
        // calculate forces between particles of one cell
        cell.iteratePairs(f);

        // then calculate forces between particles of cell + neighbors
        for (auto j : cell.getNeighbors()) {
            if (cell.getIndex() >= j->getIndex()) continue;

            for(auto pi : cell.getParticles())
                for(auto pj : j->getParticles())
                    f(*pi,*pj);
        }
    }
}

void LinkedCellContainer::calculateIteration() {
    //calculate new positions
    iterate([](Particle &p) {
            p.calculateX();
            p.saveOldF();
    });

    boundaryHandler->handle(&cells);

    clearOutflowParticles();

    //reset cell particles
    for(auto& c:cells) c.removeParticles();
    iterate([&](Particle &p) {
        assignParticle(p);
        if(gravity.present())
            p.applyGravity(gravity.get());
    });

    // calculate new f
    //iteratePairs(calculateLennardJones);
    iteratePairs([&](Particle &p1, Particle &p2){
        double epsilon = mixedEpsilon.find({p1.getEpsilon(), p2.getEpsilon()})->second;
        double sigma = mixedSigma.find({p1.getSigma(), p2.getSigma()})->second;
        calculateLennardJones(p1, p2, epsilon, sigma);
    });

    // calculate new v
    iterate([&](Particle &p) {
        p.calculateV();
    });
}

int LinkedCellContainer::getIndex(std::array<int, 3> pos) {
    if(pos[0] < 0 || pos[1] < 0 || pos[2] < 0 ||
        pos[0] >= dimensions[0] || pos[1] >= dimensions[1] || pos[2] >= dimensions[2])
        return -1;

    return pos[0] + (pos[1] + pos[2]*dimensions[1])*dimensions[0];
}

bool LinkedCellContainer::assignParticle(Particle &p) {
    int index = getIndexFromParticle(p);

    if(index < 0 || index > cells.size()){
        LOG4CXX_ERROR(linkedCellContainerLogger, "Particle out of domain was not deleted!");
        return false;
    }
    cells.at(index).addParticle(&p);
    return true;
}

std::array<int, 3> LinkedCellContainer::indexToPos(int i) {
    int z = i / (dimensions[0] * dimensions[1]);
    i -= z * (dimensions[0] * dimensions[1]);
    int y = i / dimensions[0];
    int x = i % dimensions[0];
    return { x, y, z };
}

int LinkedCellContainer::getIndexFromParticle(Particle &p) {
    std::array<int,3> x{};
    for(int i = 0; i<3;i++)
        x[i] = (int)std::floor(p.getX()[i]/cutoff_radius);

    return getIndex(x);
}

std::size_t LinkedCellContainer::size() {
    return particles.size();
}

void LinkedCellContainer::clearOutflowParticles() {
    auto& v = particles.getParticles();
    v.erase(std::remove_if(
            v.begin(), v.end(),
            [&](Particle& p) {
                return p.isOut(domain_size);
            }), v.end());
}

void LinkedCellContainer::populateNeighbours() {
    int neighborIndex = 0;
    for(auto &c : cells)
        for(int j = -1; j <= 1; j++)
            for(int k = -1; k <= 1; k++)
                for(int l = -1; l <= 1; l++) {
                    int i = c.getIndex();
                    auto pos = indexToPos(i);
                    neighborIndex = getIndex({pos[0] + j, pos[1] + k, pos[2] + l});

                    if(neighborIndex != i && neighborIndex >= 0 && neighborIndex < cells.size())
                        c.addNeighbor(&cells.at(neighborIndex));
                }

    boundaryHandler->addPeriodicNeighbours(&cells);
}

std::vector<LinkedCell>& LinkedCellContainer::getCells(){
    return cells;
}

ParticleContainer& LinkedCellContainer::getParticles() {
    return particles;
}

LinkedCellContainer::LinkedCellContainer() {
    cutoff_radius = 0;
    boundaryHandler = nullptr;
}

std::array<double, 3>& LinkedCellContainer::getDomainSize() {
    return domain_size;
}

std::array<int, 3>& LinkedCellContainer::getDimensions() {
    return dimensions;
}

BoundaryHandler *LinkedCellContainer::getBoundaryHandler() {
    return this->boundaryHandler;
}

void LinkedCellContainer::mixParameters() {
    iteratePairs([&](Particle &p1, Particle &p2){
        double eps1 = p1.getEpsilon();
        double eps2 = p2.getEpsilon();
        if(this->mixedEpsilon.find({eps1, eps2}) == this->mixedEpsilon.end()) {
            // mix epsilons and save in map
            this->mixedEpsilon.insert(std::pair<std::array<double, 2>, double>({eps1, eps2}, std::sqrt(eps1*eps2)));
        }

        double sig1 = p1.getSigma();
        double sig2 = p2.getSigma();
        if(this->mixedSigma.find({sig1, sig2}) == this->mixedSigma.end()) {
            // mix sigmas and save in map
            this->mixedSigma.insert(std::pair<std::array<double, 2>, double>({sig1, sig2}, (sig1+sig2)/2));
        }
    });
}