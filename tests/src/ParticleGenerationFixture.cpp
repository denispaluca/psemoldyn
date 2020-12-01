//
// Created by mira on 01.12.20.
//
#include <gtest/gtest.h>
#include "../../src/ParticleGenerator.h"
#include "../../src/FileReader.h"

/**
 * Fixture to write tests for //TODO
 */
class ParticleGenerationFixture : public testing::Test {
protected:
    ParticleContainer pc;
    std::vector<Particle> particles;
    std::vector<Cuboid> c;
    std::vector<Cuboid> read;
    ParticleContainer generated;
    ParticleGenerator pg;
    FileReader reader;
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

        std::string test_file_normal = "input/test_reading_normal.cuboids";
        reader.readCuboids(read, const_cast<char *>(test_file_normal.c_str()));
    }
};

bool generatedSame(Particle &p1, Particle &p2){
    return (p1.getX() == p2.getX() && p1.getF() == p2.getF() && p1.getM() == p2.getM() && p1.getType() == p2.getType());
}

TEST_F(ParticleGenerationFixture, Particle_Generation) {
    for(int i=0;i<pc.getParticles().size();i++){
        EXPECT_TRUE(generatedSame(pc.getParticles().at(i), generated.getParticles().at(i)));
    }
}

TEST_F(ParticleGenerationFixture, Adding_Cuboids_Same_Cuboids) {
    for(int i=0;i<c.size();i++){
        EXPECT_TRUE(c.at(i) == pg.getCuboids().at(i));
    }
}

TEST_F(ParticleGenerationFixture, Adding_Cuboids_Same_Particles) {
    for(int i=0;i<pc.getParticles().size();i++){
        EXPECT_TRUE(generatedSame(pc.getParticles().at(i), pg.getParticles().getParticles().at(i)));
    }
}

TEST_F(ParticleGenerationFixture, Reading_Cuboids_Normal) {
    for(int i=0;i<c.size();i++){
        EXPECT_TRUE(c.at(i) == read.at(i));
    }
}

TEST_F(ParticleGenerationFixture, Reading_Cuboids_Faulty1) {
    std::string test_file_normal = "input/test_reading_faulty1.cuboids";
    ASSERT_DEATH(reader.readCuboids(read, const_cast<char *>(test_file_normal.c_str())), "");
}