//
// Created by denis on 27.12.20.
//
#include <gtest/gtest.h>
#include <Thermostat.h>
#include <cell/LinkedCellContainer.h>
#include "xml/molsimInput.hxx"
#include "particle/ParticleGenerator.h"

class ThermostatFixture : public testing::Test{
protected:
    Thermostat* t1;
    LinkedCellContainer lcc1;
    void SetUp() override{
        auto data = input("input/input_thermostat_fixture.xml");
        t1 = new Thermostat(data->thermostat().get(), data->particle_data().is3D());
        auto pc = ParticleGenerator(data->particle_data(), t1).getParticles();
        lcc1 = LinkedCellContainer(data->domain(), pc);
    }
};

TEST_F(ThermostatFixture, Scales)