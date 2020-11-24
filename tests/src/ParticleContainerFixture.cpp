//
// Created by denis on 22.11.20.
//
#include <gtest/gtest.h>
#include "../../src/ParticleContainer.h"


class ParticleContainerFixture : public testing::Test {
protected:
    ParticleContainer pc;
    std::vector<Particle> particles;
    void SetUp() override {

    }
    void TearDown() override{

    }
};

TEST_F(ParticleContainerFixture, Size){
  EXPECT_EQ(pc.getParticles().size(), particles.size());
}
