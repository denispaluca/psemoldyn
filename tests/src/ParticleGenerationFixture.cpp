//
// Created by mira on 01.12.20.
//
#include <gtest/gtest.h>
#include "particle/ParticleGenerator.h"
#include "deprecated/FileReader.h"

/**
 * Fixture to write tests for classes and functions used in the process of particle generation
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

        // Cuboids created manually
        Cuboid cub1 = Cuboid({0.0, 0.0, 0.0}, {3, 3, 3}, 1.0, 1.0, {0.0, 0.0, 0.0}, 5, 1);
        Cuboid cub2 = Cuboid({-2.0, -2.0, -2.0}, {1, 1, 10}, 2.0, 2.0, {0.0, 0.0, 0.0}, 5, 1);
        Cuboid cub3 = Cuboid({0.0, 5.0, 0.0}, {0, 0, 0}, 1.0, 1.0, {0.0, 0.0, 0.0}, 5, 1);
        Cuboid cub4 = Cuboid({30.0, 0.0, -5.0}, {2, 1, 2}, 7.0, 1.0, {0.0, 0.0, 0.0}, 5, 1);
        Cuboid cub5 = Cuboid({3.0, 3.0, 3.0}, {10, 0, 2}, 5.0, 3.0, {0.0, 0.0, 0.0}, 5, 1);
        c.emplace_back(cub1);
        c.emplace_back(cub2);
        c.emplace_back(cub3);
        c.emplace_back(cub4);
        c.emplace_back(cub5);

        // file with manually calculated input data for the particles contained in the cuboids defined above
        std::string test_file_particles = "input/test_particles.particles";
        auto fr = new FileReader();
        fr->readParticles(particles, const_cast<char *>(test_file_particles.c_str()));
        pc = ParticleContainer(particles);

        generated = ParticleContainer();
        for(auto &cuboid : c){
            cuboid.generate(generated);
        }

        pg = ParticleGenerator();
        for (auto &cuboid : c){
            pg.addCuboid(cuboid);
        }

        // file with input data corresponding to the parameters of the cuboids defined above
        std::string test_file_normal = "input/test_reading_normal.cuboids";
        reader.readCuboids(read, const_cast<char *>(test_file_normal.c_str()));
    }
};

/**
 * Helper function for tests on generated Particles, checks for equality except for velocity field.
 * Velocity is randomly calculated according to Maxwell-Boltzmann-Distribution
 * and can therefore not be used to test if a Particle was generated correctly.
 * @param p1 the first Particle
 * @param p2 the second Particle
 * @return true if the Particles share the same values in all fields except for the velocity, false otherwise
 */
bool generatedSame(Particle &p1, Particle &p2){
    return (p1.x == p2.x && p1.f == p2.f && p1.getM() == p2.getM() && p1.getType() == p2.getType());
}

/**
 * Checks if the generate() function generates the expected Particles
 */
TEST_F(ParticleGenerationFixture, Particle_Generation) {
    for(int i=0;i<pc.getParticles().size();i++){
        EXPECT_TRUE(generatedSame(pc.getParticles().at(i), generated.getParticles().at(i)));
    }
}

/**
 * Checks if Cuboid added to ParticleGenerator is stored as expected.
 */
TEST_F(ParticleGenerationFixture, Adding_Cuboids_Same_Cuboids) {
    for(int i=0;i<c.size();i++){
        EXPECT_TRUE(c.at(i) == pg.getCuboids().at(i));
    }
}

/**
 * Checks if Particles generated after adding Cuboid to a ParticleGenerator are as expected.
 */
TEST_F(ParticleGenerationFixture, Adding_Cuboids_Same_Particles) {
    for(int i=0;i<pc.getParticles().size();i++){
        EXPECT_TRUE(generatedSame(pc.getParticles().at(i), pg.getParticles().getParticles().at(i)));
    }
}

/**
 * Checks if Cuboids are created as expected from a correct input file.
 */
TEST_F(ParticleGenerationFixture, Reading_Cuboids_Normal) {
    for(int i=0;i<c.size();i++){
        EXPECT_TRUE(c.at(i) == read.at(i));
    }
}

/**
 * Checks if program terminates if a faulty input file is read.
 */
TEST_F(ParticleGenerationFixture, Reading_Cuboids_Incomplete_Data) {
    std::string test_file_normal = "input/test_reading_incomplete_data.cuboids";
    ASSERT_DEATH(reader.readCuboids(read, const_cast<char *>(test_file_normal.c_str())), "");
}

/**
 * Checks if program / file reading terminates if a cuboid of negative size is given in input file.
 */
TEST_F(ParticleGenerationFixture, Reading_Cuboids_Negative_Size) {
    std::string test_file_normal = "input/test_reading_negative_size.cuboids";
    ASSERT_DEATH(reader.readCuboids(read, const_cast<char *>(test_file_normal.c_str())), "");
}

/**
 * Checks if program / file reading terminates if a cuboid with negative particle distance is given in input file.
 */
TEST_F(ParticleGenerationFixture, Reading_Cuboids_Negative_Distance) {
    std::string test_file_normal = "input/test_reading_negative_distance.cuboids";
    ASSERT_DEATH(reader.readCuboids(read, const_cast<char *>(test_file_normal.c_str())), "");
}

/**
 * Checks if program / file reading terminates if a cuboid with negative particle mass is given in input file.
 */
TEST_F(ParticleGenerationFixture, Reading_Cuboids_Negative_Mass) {
    std::string test_file_normal = "input/test_reading_negative_mass.cuboids";
    ASSERT_DEATH(reader.readCuboids(read, const_cast<char *>(test_file_normal.c_str())), "");
}