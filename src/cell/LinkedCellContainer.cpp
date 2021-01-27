//
// Created by mira on 08.12.20.
//

#include "LinkedCellContainer.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <utils/ForceUtils.h>
#include <xml/molsimInput.hxx>
#include <utils/XSDMapper.h>
#include <iostream>

#ifdef WITH_LOG4CXX
    #include <log4cxx/propertyconfigurator.h>
    #include <log4cxx/logger.h>

    using namespace log4cxx;
    using namespace log4cxx::helpers;

    //static logger variable linkedCellContainerLogger
    log4cxx::LoggerPtr linkedCellContainerLogger(log4cxx::Logger::getLogger("linkedcellcont"));
#endif

LinkedCellContainer::LinkedCellContainer(domain_type domain,
                                         ParticleContainer &particles){
    this->domain_size = mapDoubleVec(domain.domain_size());
    this->cutoff_radius = std::abs(domain.cutoff_radius());
    this->particles = particles;
    gravity = domain.gravity();
#ifdef _OPENMP
    useLocks = domain.useLocks();
#endif
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
#ifdef _OPENMP
        if(useLocks)
            p.initLock();
#endif
    });

    boundaryHandler = new BoundaryHandler(domain.boundary(), domain_size, dimensions);
    #ifdef WITH_LOG4CXX
        LOG4CXX_INFO(linkedCellContainerLogger, "Starting neighbor calculation");
    #endif

    populateNeighbours();

    #ifdef WITH_LOG4CXX
        LOG4CXX_INFO(linkedCellContainerLogger, "Ended neighbor calculation");
    #endif


}

void LinkedCellContainer::iterate(std::function<void(Particle &)> f) {
    particles.iterate(f);
}

void LinkedCellContainer::iteratePairs(std::function<void(Particle&, Particle&)> f) {
    //auto size = cells.size();
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (int i = 0; i < cells.size(); i++) {
        auto cell = cells[i];
        auto &cellParticles = cell.getParticles();
        if(cellParticles.empty()) continue;
        // calculate forces between particles of one cell
        cell.iteratePairs(f);

        // then calculate forces between particles of cell + neighbors
        for (auto & neighbour : cell.getNeighbors()) {
            if (i >= neighbour->getIndex())
                continue;

            auto &neighbourParticles = neighbour->getParticles();
            if(neighbourParticles.empty()) continue;

            for(auto & cellParticle : cellParticles) {
                auto &p1 = *cellParticle;
                for (auto &neighbourParticle : neighbourParticles)
                    f(p1, *neighbourParticle);
            }
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
    iteratePairs([&](Particle &p1, Particle &p2){
        double epsilon = mixedEpsilon[std::make_pair(p1.epsilon,p2.epsilon)];
        double sigma = mixedSigma[std::make_pair(p1.sigma,p2.sigma)];
#ifdef _OPENMP
        cljParallel(p1, p2, epsilon, sigma, useLocks);
#else
        calculateLennardJones(p1, p2, epsilon, sigma);
#endif
    });
    boundaryHandler->iteratePeriodicParticles(&cells, [&](Particle &p1, Particle &p2){
        double epsilon = mixedEpsilon[std::make_pair(p1.epsilon,p2.epsilon)];
        double sigma = mixedSigma[std::make_pair(p1.sigma,p2.sigma)];
        calculateLennardJones(p1, p2, epsilon, sigma);
    });


    // calculate new v
#ifdef _OPENMP
    iterate([useLocks = useLocks](Particle &p) {
        if(!useLocks)
            p.consolidateForces();
#else
    iterate([](Particle &p) {
#endif
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

        #ifdef WITH_LOG4CXX
            LOG4CXX_ERROR(linkedCellContainerLogger, "Particle out of domain was not deleted!");
        #endif

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
        x[i] = (int)std::floor(p.x[i]/cutoff_radius);

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
    std::set<double> epsilons;
    std::set<double> sigmas;
    iterate([&](Particle &p1){
       epsilons.emplace(p1.epsilon);
       sigmas.emplace(p1.sigma);
    });

    for(auto &e1 :epsilons)
        for(auto &e2 : epsilons)
            mixedEpsilon.insert(std::make_pair(std::make_pair(e1, e2), std::sqrt(e1*e2)));


    for(auto &s1 : sigmas)
        for(auto &s2 : sigmas)
            mixedSigma.insert(std::make_pair(std::make_pair(s1, s2), (s1+s2)/2));
}
