//
// Created by denis on 14.12.20.
//
#include "XSDMapper.h"

std::array<int, 3> mapIntVec(integer_vector& x){
    return {x.x(), x.y(), x.z()};
}

std::array<double, 3> mapDoubleVec(double_vector& x){
    return {x.x(), x.y(), x.z()};
}

integer_vector mapToIntVec(std::array<int, 3> x){
    return {x[0], x[1], x[2]};
}

double_vector mapToDoubleVec(std::array<double, 3> x){
    return {x[0], x[1], x[2]};
}

ParticleSphere mapParticleSphere(sphere& c){
    return {
            mapDoubleVec(c.center()),
            mapDoubleVec(c.v()),
            c.r(),
            c.h(),
            c.m(),
            c.epsilon(),
            c.sigma(),
            c.fixed()
    };
}

Cuboid mapCuboid(cuboid& c){
    return {
        mapDoubleVec(c.position()),
        mapIntVec(c.size()),
        c.distance(),
        c.mass(),
        mapDoubleVec(c.velocity()),
        c.epsilon(),
        c.sigma(),
        c.membrane(),
        c.r0(),
        c.k(),
		c.fixed()
    };
}

Particle mapParticle(particle& p){
    return {
            mapDoubleVec(p.x()),
            mapDoubleVec(p.v()),
            p.m(),
            mapDoubleVec(p.f()),
            mapDoubleVec(p.old_f()),
            p.type(),
            p.epsilon(),
            p.sigma(),
            p.r0(),
            p.km(),
            p.fixed()
    };
}

particle mapParticleToXML(Particle &p){
    return {
        mapToDoubleVec(p.x),
        mapToDoubleVec(p.getV()),
        p.getM(),
        mapToDoubleVec(p.f),
        mapToDoubleVec(p.getOldF()),
        p.getType(),
        p.epsilon,
        p.sigma,
        p.r0,
        p.km,
        p.fixed
    };
}

std::pair<int, std::array<double, 3>> mapExtraForce(extra_force& p) {
    return {
            std::make_pair(p.index(), mapDoubleVec(p.f_vector()))
    };
}

/*
std::vector<std::pair<int, std::array<double, 3>>> mapExtraForces(extra_force& p) {
    return {
            std::make_vector(
    }
}
 */