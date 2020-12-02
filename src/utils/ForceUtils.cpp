//
// Created by denis on 01.12.20.
//

#include <cmath>
#include "ForceUtils.h"

#define EPSILON 5.0
#define SIGMA  1.0


/**
 * Calculate second norm cubed of array with length 3.
 * @param x Input coordinates
 * @return (||x||_2)^3
 */
static double radiusPow3(const std::array<double, 3> &x) {
    double result = x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
    return pow(sqrt(result), 3);
}

/**
 * Calculate second norm of array with length 3.
 * @param x Input coordinates
 * @return ||x||_2
 */
static inline double radius(const std::array<double, 3> &x) {
    return sqrt(x[0]*x[0] + x[1]*x[1] + x[2]*x[2]);
}

void calculateF(Particle &p1, Particle &p2) {
    std::array<double, 3> p1_x = p1.getX(),
            xDiff = p2.getX(), f12;
    xDiff[0] -= p1_x[0];
    xDiff[1] -= p1_x[1];
    xDiff[2] -= p1_x[2];

    double divider = radiusPow3(xDiff), vf;
    // calculate F_ij
    if (divider) {
        vf = (p1.getM() * p2.getM()) / divider;
        f12 = {vf*xDiff[0], vf*xDiff[1], vf*xDiff[2]};
        p1.addF(f12);
        p2.addF({-f12[0], -f12[1], -f12[2]});
    }
}

void calculateLennardJones(Particle &p1, Particle &p2) {
    std::array<double, 3> p1_x = p1.getX(),
            xDiff = p2.getX();
    xDiff[0] -= p1_x[0];
    xDiff[1] -= p1_x[1];
    xDiff[2] -= p1_x[2];

    double divider = radius(xDiff);

    if(divider) {
        double sigDivPow6 = pow(SIGMA/divider, 6);
        double vf = ((24*EPSILON) / (divider*divider)) * (sigDivPow6 - 2*sigDivPow6*sigDivPow6);

        std::array<double, 3> f12 = {vf*xDiff[0], vf*xDiff[1], vf*xDiff[2]};

        p1.addF(f12);
        p2.addF({-f12[0], -f12[1], -f12[2]});
    }
}
