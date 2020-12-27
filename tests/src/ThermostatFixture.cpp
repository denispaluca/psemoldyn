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
    Thermostat* t2;
    LinkedCellContainer lcc2;
    void SetUp() override{
        std::unique_ptr<molsimInput> data;
        ParticleContainer pc;

        data = input("input/input_thermostat_fixture.xml");
        t1 = new Thermostat(data->thermostat().get(), data->particle_data().is3D());
        pc = ParticleGenerator(data->particle_data(), t1).getParticles();
        lcc1 = LinkedCellContainer(data->domain(), pc);

        data = input("input/input_thermostat_fixture_change.xml");
        t2 = new Thermostat(data->thermostat().get(), data->particle_data().is3D());
        pc = ParticleGenerator(data->particle_data(), t2).getParticles();
        lcc2 = LinkedCellContainer(data->domain(), pc);
    }
};

TEST_F(ThermostatFixture, Scales){
    for(int i = 0; i < 100; i++){
        lcc1.calculateIteration();
    }
    auto temp1 = t1->getCurrentTemp(lcc1);
    t1->scale(lcc1);
    auto t_init = t1->getCurrentTemp(lcc1);
    EXPECT_NE(temp1, t_init);
    EXPECT_DOUBLE_EQ(t_init, 100);
}

TEST_F(ThermostatFixture, InitTemp_SET){
    auto t_init = t2->getCurrentTemp(lcc2);
    EXPECT_DOUBLE_EQ(t_init, t2->getInitTemp());
}