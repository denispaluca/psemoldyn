//
// Created by denis on 16.12.20.
//

#include <utils/ForceUtils.h>
#include "BoundaryHandler.h"

constexpr double B_EFFECT = 1.1225;

BoundaryHandler::BoundaryHandler(boundaries_type boundaries, std::array<double, 3> domainSize,
                                 std::array<int, 3> dimensions):
                                 boundaries(boundaries),domainSize(domainSize), dimensions(dimensions){}

void BoundaryHandler::prepareCounter(Particle &p) {
    auto x = p.getX();
    counter.getF()[0] = 0;
    counter.getF()[1] = 0;
    counter.getF()[2] = 0;
    counter.setM(p.getM());
    counter.getX()[0] = x[0];
    counter.getX()[1] = x[1];
    counter.getX()[2] = x[2];
}

void BoundaryHandler::iterateCellsAtBoundary(Boundaries b, const std::function<void(LinkedCell &)>& f) {
    switch (b) {
        case left:
            for(int i = 0;i < dimensions[1]; i++)
                for(int j = 0; j < dimensions[2]; j++)
                    f(cells->at(getIndex({0,i,j})));
            return;
        case right:
            for(int i = 0;i < dimensions[1]; i++)
                for(int j = 0; j < dimensions[2]; j++)
                    f(cells->at(getIndex({dimensions[0]-1, i,j})));
            return;
        case bottom:
            for(int i = 0;i < dimensions[0]; i++)
                for(int j = 0; j < dimensions[2]; j++)
                    f(cells->at(getIndex({i,0,j})));
            return;
        case top:
            for(int i = 0;i < dimensions[0]; i++)
                for(int j = 0; j < dimensions[2]; j++)
                    f(cells->at(getIndex({i,dimensions[1] - 1,j})));
            return;
        case front:
            for(int i = 0;i < dimensions[0]; i++)
                for(int j = 0; j < dimensions[1]; j++)
                    f(cells->at(getIndex({i,j,0})));
            return;
        case back:
            for(int i = 0;i < dimensions[0]; i++)
                for(int j = 0; j < dimensions[1]; j++)
                    f(cells->at(getIndex({i,j, dimensions[2] - 1})));
            return;
    }
}

void BoundaryHandler::handle(std::vector<LinkedCell>* cells) {
    this->cells = cells;
    handleBoundary(Boundaries::top, boundaries.top());
    handleBoundary(Boundaries::bottom, boundaries.bottom());
    handleBoundary(Boundaries::front, boundaries.front());
    handleBoundary(Boundaries::back, boundaries.back());
    handleBoundary(Boundaries::left, boundaries.left());
    handleBoundary(Boundaries::right, boundaries.right());
}

void BoundaryHandler::handleBoundary(Boundaries boundary, boundary_type& value) {
    if(value == Boundary::reflective)
        reflect(boundary);
    else if(value == Boundary::periodic)
        period(boundary);
}

void BoundaryHandler::iterateParticlesAtBoundary(Boundaries b, const std::function<void(Particle &)> &f) {
    auto func = [&](LinkedCell &c) {
        for (auto p : c.getParticles())
            f(*p);
    };
    iterateCellsAtBoundary(b, func);
}

void BoundaryHandler::reflect(Boundaries b) {
    auto func = [&](Particle& p){
        bool isThere;
        auto x = p.getX();
        prepareCounter(p);
        switch (b) {
            case left:
                isThere = x[0] < B_EFFECT;
                counter.getX()[0] = -x[0];
                break;
            case right:
                isThere = domainSize[0] - x[0] < B_EFFECT;
                counter.getX()[0] = 2 * domainSize[0] - x[0];
                break;
            case bottom:
                isThere = x[1] < B_EFFECT;
                counter.getX()[1] = -x[1];
                break;
            case top:
                isThere = domainSize[1] - x[1] < B_EFFECT;
                counter.getX()[1] = 2 * domainSize[1] - x[1];
                break;
            case front:
                isThere = x[2] < B_EFFECT;
                counter.getX()[2] = -x[2];
                break;
            case back:
                isThere = domainSize[2] - x[2] < B_EFFECT;
                counter.getX()[2] = 2 * domainSize[2] - x[2];
                break;
        }
        if(isThere) calculateLennardJones(p, counter);
    };

    iterateParticlesAtBoundary(b,func);
}

void BoundaryHandler::period(Boundaries b) {
    auto func = [&](Particle& p){
        auto x = p.getX();
        switch (b) {
            case top:
                if(x[2] > domainSize[2])
                    x[2] -= domainSize[2];
                return;
                return;
            case bottom:
                if(x[1] < 0)
                    x[1] += domainSize[1];
                return;
            case front:
                if(x[2] < 0)
                    x[2] += domainSize[2];
                return;
            case back:
                if(x[2] > domainSize[2])
                    x[2] -= domainSize[2];
                return;
                return;
            case left:
                if(x[0] < 0)
                    x[0] += domainSize[0];
                return;
            case right:
                if(x[0] > domainSize[0])
                    x[0] -= domainSize[0];
                return;
        }
    };

    iterateParticlesAtBoundary(b,func);
}

int BoundaryHandler::getIndex(std::array<int, 3> pos) {
    if(pos[0] < 0 || pos[1] < 0 || pos[2] < 0 ||
       pos[0] >= dimensions[0] || pos[1] >= dimensions[1] || pos[2] >= dimensions[2])
        return -1;

    return pos[0] + (pos[1] + pos[2]*dimensions[1])*dimensions[0];
}
