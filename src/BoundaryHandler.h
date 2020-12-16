//
// Created by denis on 16.12.20.
//

#pragma once
#include "xml/molsimInput.hxx"
#include "Particle.h"

enum Boundary{
    top, bottom, front, back, left, right
};

class BoundaryHandler {
private:
    boundary_type boundary;
    std::array<double, 3> dimensions{};
    void handleBoundary(Particle& p, Boundary b);
public:
    BoundaryHandler(boundary_type& boundary, std::array<double, 3> dimensions);
    void applyForce(Particle& p);
};
