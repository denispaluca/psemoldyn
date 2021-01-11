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
        ASSERT_FLOAT_EQ(std::sqrt(i.first[0]*i.first[1]), i.second);
    }
    for (auto &i : container.getMixedSigma()) {
        ASSERT_FLOAT_EQ((i.first[0]+i.first[1])/2, i.second);
    }
}

/**
 * Checks if mixParameters calculates all possible mixed parameters
 */
TEST_F(ParticleTypesFixture, mixedAll){
    container.iteratePairs([&](Particle &p1, Particle &p2){
        ASSERT_TRUE(container.getMixedEpsilon().find({p1.getEpsilon(), p2.getEpsilon()}) != container.getMixedEpsilon().end());
        ASSERT_TRUE(container.getMixedEpsilon().find({p2.getEpsilon(), p1.getEpsilon()}) != container.getMixedEpsilon().end());
        ASSERT_TRUE(container.getMixedSigma().find({p1.getSigma(), p2.getSigma()}) != container.getMixedSigma().end());
        ASSERT_TRUE(container.getMixedSigma().find({p2.getSigma(), p1.getSigma()}) != container.getMixedSigma().end());
    });
}


