//
// Created by mira on 16.12.20.
//

#include <gtest/gtest.h>
#include "../../src/LinkedCell.h"
#include "../../src/LinkedCellContainer.h"


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

        // set up for LinkedCellContainer tests
        containerParticles = ParticleContainer();
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                Particle p = Particle({(double)i, (double)j, 0}, {1, 0, 0}, i*5+j, 0);
                containerParticles.push(p);
            }
        }
        containerCells = std::vector<LinkedCell>();
        for(int i = 0; i < 6; i += 2.0) {
            for(int j = 0; j < 6; j += 2) {
                LinkedCell cell = LinkedCell({(double)i, (double)j, 0}, 2, i*5+j);
                containerCells.emplace_back(cell);
            }
        }
        lcc = LinkedCellContainer({6, 6, 6}, 2, containerParticles);
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
        EXPECT_EQ(singleCell.getParticles().at(i)->getF(), 19*20/2);
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
 * Checks if cell positions are set correctly.
 */
TEST_F(LinkedCellContainerFixture, cellPositions){
    for(int i = 0; i < containerCells.size(); i++){
        EXPECT_EQ(containerCells.at(i).getPosition(), lcc.getCells().at(i));
    }
}

/**
 * Checks if added particles belong to their cells and are assigned correctly (assignParticle).
 */
TEST_F(LinkedCellContainerFixture, correctParticleAssignment){
    for(auto c : lcc.getCells()) {
        for(auto p : c.getParticles()) {
            std::array<double, 3> xDiff = {p->getX()[0]-c.getPosition()[0],
                                           p->getX()[1]-c.getPosition()[1],
                                           p->getX()[2]-c.getPosition()[2]
                                           };
            EXPECT_TRUE(xDiff[0] >= 0 && xDiff[0] < 2 && xDiff[1] >= 0 && xDiff[1] < 2 && xDiff[2] >= 0 && xDiff[2] < 2);
        }
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

/**
 * Checks if correct neighbors were added.
 */
TEST_F(LinkedCellContainerFixture, correctNeighbours){
    for(auto c : lcc.getCells()) {
        for(auto n : c.getNeighbors()) {
            std::array<double, 3> xDiff = {n->getPosition()[0]-c.getPosition()[0],
                                           n->getPosition()[1]-c.getPosition()[1],
                                           n->getPosition()[2]-c.getPosition()[2]
            };
            EXPECT_TRUE(xDiff[0] == 2 || xDiff[1] == 2 || xDiff[2] == 2);
        }
    }
}

/**
 * Checks if iterating particle pairs works as expected.
 */
TEST_F(LinkedCellContainerFixture, iterateLCCPairs){
    lcc.iteratePairs([](Particle &p1, Particle &p2){
        p1.addF({p1.getM(), 0, 0});
        p2.addF({p2.getM(), 0, 0});
    });

    for(int i = 0; i < containerParticles.size(); i++){
        EXPECT_EQ(lcc.getParticles().getParticles().at(i).getF(), containerParticles.size()*(containerParticles.size()+1)/2);
    }
}

/**
 * Checks if calculating corresponding cell index from a particle's position position works as expected.
 */
TEST_F(LinkedCellContainerFixture, correctIndexFromPosition){
    for(int i = 0; i < lcc.getCells().size(); i++)
        for(auto p : lcc.getCells().at(i).getParticles())
            EXPECT_EQ(lcc.getIndexFromParticle(p), i);
}

/**
 * Checks if outflow boundary condition works as expected.
 */
TEST_F(LinkedCellContainerFixture, testOutflowHandling){
    // current implementation: outflow particles are automatically cleared
    lcc.iterate([](Particle &p){
        p.updateDT(1);
    });

    lcc.calculateIteration();

    EXPECT_EQ(lcc.getParticles().size(), 20);
}