//
// Created by mira on 31.12.20.
//
#include <gtest/gtest.h>
#include <cell/LinkedCellContainer.h>
#include "Container.h"
#include "Thermostat.h"
#include "Simulation.h"
#include <cmath>

class ParticleTypesFixture : public testing::Test {
protected:
    LinkedCellContainer container;
    void SetUp() override {
        std::unique_ptr<molsimInput> data = input("input/input_particletypes_fixture.xml");
        Thermostat *t = new Thermostat(data->thermostat().get(), data->particle_data().is3D());
        ParticleContainer pc = ParticleGenerator(data->particle_data(), t).getParticles();
        container = LinkedCellContainer(data->domain(), pc);

        container.mixParameters();
    }
};


/**
 * Checks if mixParameters calculates the parameters correctly
 */
TEST_F(ParticleTypesFixture, mixedCorrectly){
    for (auto &i : container.getMixedEpsilon()) {
        ASSERT_FLOAT_EQ(std::sqrt(i.first.first*i.first.second), i.second);
    }
    for (auto &i : container.getMixedSigma()) {
        ASSERT_FLOAT_EQ((i.first.first+i.first.second)/2, i.second);
    }
}

/**
 * Checks if mixParameters calculates all possible mixed parameters
 */
TEST_F(ParticleTypesFixture, mixedAll){
    container.iteratePairs([&](Particle &p1, Particle &p2){
        ASSERT_TRUE(container.getMixedEpsilon().find({p1.epsilon, p2.epsilon}) != container.getMixedEpsilon().end());
        ASSERT_TRUE(container.getMixedEpsilon().find({p2.epsilon, p1.epsilon}) != container.getMixedEpsilon().end());
        ASSERT_TRUE(container.getMixedSigma().find({p1.sigma, p2.sigma}) != container.getMixedSigma().end());
        ASSERT_TRUE(container.getMixedSigma().find({p2.sigma, p1.sigma}) != container.getMixedSigma().end());
    });
}


