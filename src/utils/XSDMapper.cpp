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

ParticleSphere mapParticleSphere(sphere& c){
    return {
            mapDoubleVec(c.center()),
            mapDoubleVec(c.v()),
            c.r(),
            c.h(),
            c.m(),
            c.epsilon(),
            c.sigma()
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
        c.sigma()
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
        p.sigma()
    };
}