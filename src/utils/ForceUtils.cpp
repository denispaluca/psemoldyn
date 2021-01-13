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
 * Calculate square sum of array elements.
 * @param x Input coordinates
 * @return Square sum
 */
static inline double squareSum(const std::array<double, 3> &x) {
    return x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
}

/**
 * Calculate x^3.
 * @param x input
 * @return x^3
 */
static inline double pow3(const double x){
    return x*x*x;
}

/**
 * Calculate x^6.
 * @param x input
 * @return x^6
 */
static inline double pow6(const double x){
    const double r = pow3(x);
    return r*r;
}

/*
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
 */

void calculateLennardJones(Particle &p1, Particle &p2, double epsilon, double sigma) {
    std::array<double, 3> p1_x = p1.x,
            xDiff = {p2.x[0], p2.x[1], p2.x[2]};
    xDiff[0] -= p1_x[0];
    xDiff[1] -= p1_x[1];
    xDiff[2] -= p1_x[2];

    double divider = squareSum(xDiff);

    if(divider) {
        double sigDivPow6 = pow6(sigma)/pow3(divider);
        double vf = ((24*epsilon) / divider) * (sigDivPow6 - 2*sigDivPow6*sigDivPow6);

        std::array<double, 3> f12 = {vf*xDiff[0], vf*xDiff[1], vf*xDiff[2]};

        p1.addF(f12);
        p2.addF({-f12[0], -f12[1], -f12[2]});
    }
}
