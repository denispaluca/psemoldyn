//
// Created by denis on 01.12.20.
//

#include <cmath>
#include <particle/ParticleContainer.h>
#include "ForceUtils.h"
#include "ArrayUtils.h"

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
#ifdef _OPENMP
void cljParallel(Particle &p1, Particle &p2, double epsilon, double sigma, bool useLocks) {
    std::array<double, 3> xDiff;
    for(int i = 0; i < 3; i++)
        xDiff[i] = p2.x[i] - p1.x[i];

    double divider = squareSum(xDiff);

    double sigDivPow6 = pow6(sigma)/pow3(divider);
    double vf = ((24*epsilon) / divider) * (sigDivPow6 - 2*sigDivPow6*sigDivPow6);

    for(int i = 0; i < 3; i++)
        xDiff[i] *= vf;

    if(useLocks){
        p1.setLock();
        for(int i = 0; i < 3; ++i)
            p1.f[i] += xDiff[i];
        p1.unlock();

        p2.setLock();
        for(int i = 0; i < 3; ++i)
            p2.f[i] -= xDiff[i];
        p2.unlock();
    } else {
        p1.addF(xDiff);
        p2.addF({-xDiff[0],-xDiff[1],-xDiff[2]});
    }
}
#endif


void calculateLennardJones(Particle &p1, Particle &p2, double epsilon, double sigma){
    std::array<double, 3> xDiff = {p2.x[0] - p1.x[0], p2.x[1] - p1.x[1], p2.x[2] - p1.x[2]};
    double divider = squareSum(xDiff);

    double sigDivPow6 = pow6(sigma)/pow3(divider);
    double vf = ((24*epsilon) / divider) * (sigDivPow6 - 2*sigDivPow6*sigDivPow6);

    std::array<double, 3> f12 = {vf*xDiff[0], vf*xDiff[1], vf*xDiff[2]};

    if (!p1.fixed) {
        for(int i = 0; i < 3; ++i)
            p1.f[i] += f12[i];
    }

    if (!p2.fixed) {
        for(int i = 0; i < 3; ++i)
            p2.f[i] -= f12[i];
    }

}

void calculateMembrane(Particle &p1, Particle &p2, double epsilon, double sigma) {
    /*
    if (p1.uid >= p2.uid) {
        return;
    }
     */

    double t = ((p1.x[0]-p2.x[0])*(p1.x[0]-p2.x[0]))
               +((p1.x[1]-p2.x[1])*(p1.x[1]-p2.x[1]))
               +((p1.x[2]-p2.x[2])*(p1.x[2]-p2.x[2]));
    double abstand = sqrt(t);

    if (p1.laterMembraneParticles.at(0) == p2.uid || p2.laterMembraneParticles.at(0) == p1.uid) {
        calculateMembraneForce(p1, p2, false, abstand);
    } else if (p1.laterMembraneParticles.at(1) == p2.uid || p2.laterMembraneParticles.at(1) == p1.uid) {
        calculateMembraneForce(p1, p2, true, abstand);
    } else if (p1.laterMembraneParticles.at(2) == p2.uid || p2.laterMembraneParticles.at(2) == p1.uid) {
        calculateMembraneForce(p1, p2, false, abstand);
    } else if (p1.laterMembraneParticles.at(3) == p2.uid || p2.laterMembraneParticles.at(3) == p1.uid) {
        calculateMembraneForce(p1, p2, true, abstand);
    } else  { //(abstand < 1.12246 * sigma)
        calculateLennardJones(p1, p2, epsilon, sigma);
    }
}

void calculateMembraneForce(Particle &p1, Particle &p2, bool diagonal, double x) {
    p1.debug ++;
    p2.debug ++;

    std::array<double, 3> f12 = {0.0, 0.0, 0.0};

    if (diagonal) {
        x -= (1.414213562 * p1.r0);
    } else {
        x -= p1.r0;
    }

    x *= p1.km;

    f12[0] = x * (p2.x[0]-p1.x[0]);
    f12[1] = x * (p2.x[1]-p1.x[1]);
    f12[2] = x * (p2.x[2]-p1.x[2]);

    /*
    if (f12[0] > 100 || f12[1] > 100 || f12[2] > 100) {
        bool gzcdu = false;
    }
     */

    p1.f[0] += f12[0];
    p1.f[1] += f12[1];
    p1.f[2] += f12[2];

    p2.f[0] -= f12[0];
    p2.f[1] -= f12[1];
    p2.f[2] -= f12[2];
}

void setNeighbours(std::vector<Particle> &particles, int pos, int length, int x) {
    int a, b, c, d;
    for (int i = pos; i<pos+length; i++) {
        if (((i-pos)+1)%x > 0 && i+1 < pos+length) {
            a = i+1;
            particles.at(i).laterMembraneParticles.at(0) = particles.at(a).uid;
        } else {
            particles.at(i).laterMembraneParticles.at(0) = -1;
        }
        if ((i-pos)+x-1 < pos+length && (i-pos)%x -1 >= 0) {
            b = i+x-1;
            particles.at(i).laterMembraneParticles.at(1) = particles.at(b).uid;
        } else {
            particles.at(i).laterMembraneParticles.at(1) = -1;
        }
        if ((i-pos)+x < pos+length) {
            c = i+x;
            particles.at(i).laterMembraneParticles.at(2) = particles.at(c).uid;
        } else {
            particles.at(i).laterMembraneParticles.at(2) = -1;
        }
        if (((i-pos)+1)%x > 0 && i+x+1 < pos+length) {
            d = i+x+1;
            particles.at(i).laterMembraneParticles.at(3) = particles.at(d).uid;
        } else {
            particles.at(i).laterMembraneParticles.at(3) = -1;
        }
    }
    return;
}