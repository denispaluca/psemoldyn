//
// Created by denis on 16.12.20.
//

#include <utils/ForceUtils.h>
#include "BoundaryHandler.h"
#define B_EFFECT 1.225

BoundaryHandler::BoundaryHandler(boundary_type& boundary, std::array<double, 3> dimensions):
    boundary(boundary), dimensions(dimensions){}

void BoundaryHandler::applyForce(Particle &p) {
    if(boundary.top()) handleBoundary(p, Boundary::top);
    if(boundary.bottom()) handleBoundary(p, Boundary::bottom);
    if(boundary.front()) handleBoundary(p, Boundary::front);
    if(boundary.back()) handleBoundary(p, Boundary::back);
    if(boundary.left()) handleBoundary(p, Boundary::left);
    if(boundary.right()) handleBoundary(p, Boundary::right);
}

void BoundaryHandler::handleBoundary(Particle &p, Boundary b) {
    Particle q = Particle(p);
    bool isThere;
    auto x = p.getX();
    switch (b) {
        case left:
            isThere = x[0] < B_EFFECT;
            q.getX()[0] = -x[0];
            break;
        case right:
            isThere = dimensions[0] - x[0] < B_EFFECT;
            q.getX()[0] = 2*dimensions[0] - x[0];
            break;
        case bottom:
            isThere = x[1] < B_EFFECT;
            q.getX()[1] = -x[1];
            break;
        case top:
            isThere = dimensions[1] - x[1] < B_EFFECT;
            q.getX()[1] = 2*dimensions[1] - x[1];
            break;
        case front:
            isThere = x[2] < B_EFFECT;
            q.getX()[2] = -x[2];
            break;
        case back:
            isThere = dimensions[2] - x[2] < B_EFFECT;
            q.getX()[2] = 2*dimensions[2] - x[2];
            break;
    }

    if(isThere) calculateLennardJones(p,q);
}
