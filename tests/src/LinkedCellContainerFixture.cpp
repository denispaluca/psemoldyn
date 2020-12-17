//
// Created by mira on 16.12.20.
//

#include <gtest/gtest.h>
#include <particle/Particle.h>
#include <cell/LinkedCell.h>
#include <particle/ParticleContainer.h>
#include <cell/LinkedCellContainer.h>
#include "xml/molsimInput.hxx"
#include "xml/molsimInput.cxx"


/**
 * Fixture to write tests for classes and functions used in the process of particle generation
 */
class LinkedCellContainerFixture : public testing::Test {
protected:
    LinkedCell singleCell;
    std::vector<LinkedCell> singleCellNeighbors;
    ParticleContainer singleCellParticles;

    LinkedCellContainer lcc;
    ParticleContainer containerParticles;
    std::vector<LinkedCell> containerCells;
    void SetUp() override {
        // set up for LinkedCell tests
        singleCell = LinkedCell();
        singleCellNeighbors = {LinkedCell(), LinkedCell(), LinkedCell(), LinkedCell(), LinkedCell(), LinkedCell()};

        singleCellParticles = ParticleContainer();
        for(int i = 0; i < 20; i++) {
            Particle p = Particle({0, 0, 0}, {0, 0, 0}, i, 0);
            singleCellParticles.push(p);
        }

        //add all particles to singleCell
        singleCellParticles.iterate([&](Particle& p){
            singleCell.addParticle(&p);
        });

        // set up for LinkedCellContainer tests
        containerParticles = ParticleContainer();
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                Particle p = Particle({(double)i, (double)j, 0}, {1, 0, 0}, i*5+j, 0);
                containerParticles.push(p);
            }
        }
        containerCells = std::vector<LinkedCell>();
        domain_type data = input("input/input_linked_cell_fixture.xml")->domain();
        lcc = LinkedCellContainer(data, containerParticles);
        for(int i = 0; i < 6; i += 2) {
            for(int j = 0; j < 6; j += 2) {
                for(int k = 0; k < 6; k +=2){
                    LinkedCell cell = LinkedCell(lcc.getIndex({i, j, k}));
                    containerCells.emplace_back(cell);
                }
            }
        }
    }
};

//----------------------------------- Tests for LinkedCell-specific functions --------------------------------//

/**
 * Checks if correct number of neighbors was added.
 */
TEST_F(LinkedCellContainerFixture, addingNeighbourToCell){
    for(auto c : singleCellNeighbors)
        singleCell.addNeighbor(&c);

    EXPECT_EQ(singleCellNeighbors.size(), singleCell.getNeighbors().size());
}

/**
 * Checks if particles are removed correctly.
 */
TEST_F(LinkedCellContainerFixture, removeParticlesFromCell){
    singleCell.removeParticles();
    EXPECT_EQ(singleCell.getParticles().size(), 0);
}

/**
 * Checks if correct number of particles was added.
 */
TEST_F(LinkedCellContainerFixture, addParticlesToCell){
    EXPECT_EQ(singleCellParticles.size(), singleCell.getParticles().size());
}

/**
 * Checks if iterating in pairs works as expected..
 */
TEST_F(LinkedCellContainerFixture, iteratePairsInCell){
    singleCell.iteratePairs([](Particle &p1, Particle &p2){
        p1.addF({p1.getM(), 0, 0});
        p2.addF({p2.getM(), 0, 0});
    });

    for(int i = 0; i < singleCellParticles.size(); i++){
        EXPECT_DOUBLE_EQ(singleCell.getParticles().at(i)->getF()[0], 19.0*i);
    }
}


//----------------------------------- Tests for LinkedCellContainer functionality --------------------------------//

/**
 * Checks if correct number of cells was created.
 */
TEST_F(LinkedCellContainerFixture, cellInitializations){
    EXPECT_EQ(lcc.getCells().size(), containerCells.size());
}

/**
 * Checks if index is set correctly in LinkedCell.
 */
TEST_F(LinkedCellContainerFixture, cellIndex){
    for(int i = 0; i < lcc.getCells().size(); i++) {
        EXPECT_EQ(lcc.getCells().at(i).getIndex(), i);
    }
}

/**
 * Checks if all particles were distributed to cells.
 */
TEST_F(LinkedCellContainerFixture, allParticlesAssigned){
    int particlesInCells = 0;
    for(auto c : lcc.getCells())
        particlesInCells += c.getParticles().size();
    EXPECT_EQ(particlesInCells, containerParticles.size());
}

///REMOVED CUS CELL CHANGE
///**
// * Checks if correct neighbors were added.
// */
TEST_F(LinkedCellContainerFixture, correctNeighbours){
    for(auto c : lcc.getCells()) {
        for(auto n : c.getNeighbors()) {
            auto pos2 = lcc.indexToPos(n->getIndex());
            auto pos1 = lcc.indexToPos(c.getIndex());
            std::array<int, 3> xDiff = {pos2[0]-pos1[0],
                                           pos2[1]-pos1[1],
                                           pos2[2]-pos1[2]};

            EXPECT_TRUE(xDiff[0] == -1 || xDiff[0] == 0 || xDiff[0] == 1);
            EXPECT_TRUE(xDiff[1] == -1 || xDiff[1] == 0 || xDiff[1] == 1);
            EXPECT_TRUE(xDiff[2] == -1 || xDiff[2] == 0 || xDiff[2] == 1);
        }
    }
}

/**
 * Check if indexing works correctly.
 */
TEST_F(LinkedCellContainerFixture, indexCorrect){
    for(int i = 0; i < lcc.getCells().size(); i++){
        EXPECT_EQ(lcc.getIndex(lcc.indexToPos(i)), i);
    }
}