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

Cuboid mapCuboid(cuboid& c){
    return {
        mapDoubleVec(c.position()),
        mapIntVec(c.size()),
        c.distance(),
        c.mass(),
        mapDoubleVec(c.velocity()),
        c.meanv()
    };
}
Particle& mapParticle(particle& p){
    auto particle = Particle (
        mapDoubleVec(p.x()),
        mapDoubleVec(p.v()),
        p.m()
    );

    return particle;
}