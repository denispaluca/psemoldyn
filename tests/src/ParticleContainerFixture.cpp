//
// Created by denis on 22.11.20.
//
#include <gtest/gtest.h>
#include "../../src/ParticleContainer.h"

/**
 * Fixture to write tests for the ParticleContainer class.
 */
class ParticleContainerFixture : public testing::Test {
protected:
    ParticleContainer pc;
    std::vector<Particle> particles;
    void SetUp() override {
      for(int i=0;i<20;i++) {
        auto p = Particle({0, 0, 0}, {0, 0, 0}, i, 0);
        auto p1 = Particle(p);
        pc.push(p);
        particles.emplace_back(p);
      }
    }
};
/**
 * Checks if correct number of particles was pushed.
 */
TEST_F(ParticleContainerFixture, Size){
  EXPECT_EQ(pc.getParticles().size(), particles.size());
}

/**
 * Checks if the particles pushed are the same as the
 * as the ones in a simple vector.
 */
TEST_F(ParticleContainerFixture, Equality){
  for(int i=0;i<particles.size();i++){
    EXPECT_TRUE(particles.at(i) == pc.getParticles().at(i));
  }
}

/**
 * Checks if the iterate function works the same as
 * a for-loop (also checks if addF works).
 */
TEST_F(ParticleContainerFixture, Iterator){
  pc.iterate([](Particle& p){
      std::array<double, 3> f = {1,1,1};
      p.addF(f);
      EXPECT_EQ(p.getF(), f);
  });

  std::array<double, 3> f = {1,1,1};
  for(auto p : pc.getParticles()){
    EXPECT_EQ(p.getF(), f);
  }
}
