//
// Created by mira on 01.12.20.
//
#include <gtest/gtest.h>
#include "../../src/ParticleGenerator.h"

/**
 * Fixture to write tests for the ParticleContainer class.
 */
class ParticleContainerFixture : public testing::Test {
protected:
    ParticleContainer pc;
    std::vector<Particle> particles;
    std::vector<Cuboid> c;
    ParticleContainer generated;
    ParticleGenerator pg;
    void SetUp() override {

        // 3 Cuboids with 2x2x2 Particles each
        for(int i = 0; i < 3; i++){
            std::array<double, 3> pos = {0.0, i*2.0, 0.0};
            Cuboid cub = Cuboid(pos, {2, 2, 2}, 1.0, 1.0, {0.0, 0.0, 0.0}, 0.0);
            c.emplace_back(cub);
            Particle p1 = Particle(pos, {0.0, 0.0, 0.0}, 1.0);
            Particle p2 = Particle({pos[0], pos[1], pos[2]+1.0}, {0.0, 0.0, 0.0}, 1.0);
            Particle p3 = Particle({pos[0], pos[1]+1.0, pos[2]}, {0.0, 0.0, 0.0}, 1.0);
            Particle p4 = Particle({pos[0], pos[1]+1.0, pos[2]+1.0}, {0.0, 0.0, 0.0}, 1.0);
            Particle p5 = Particle({pos[0]+1.0, pos[1], pos[2]}, {0.0, 0.0, 0.0}, 1.0);
            Particle p6 = Particle({pos[0]+1.0, pos[1], pos[2]+1.0}, {0.0, 0.0, 0.0}, 1.0);
            Particle p7 = Particle({pos[0]+1.0, pos[1]+1.0, pos[2]}, {0.0, 0.0, 0.0}, 1.0);
            Particle p8 = Particle({pos[0]+1.0, pos[1]+1.0, pos[2]+1.0}, {0.0, 0.0, 0.0}, 1.0);

            pc.push(p1);
            pc.push(p2);
            pc.push(p3);
            pc.push(p4);
            pc.push(p5);
            pc.push(p6);
            pc.push(p7);
            pc.push(p8);
        }

        generated = ParticleContainer();
        for(auto &cuboid : c){
            cuboid.generate(generated);
        }

        pg = ParticleGenerator();
        for (auto &cuboid : c){
            pg.addCuboid(cuboid);
        }
    }
};