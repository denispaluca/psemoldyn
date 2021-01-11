//
// Created by denis on 17.12.20.
//

#include <gtest/gtest.h>
#include <cell/LinkedCellContainer.h>

class BoundaryHandlerFixture : public testing::Test {
protected:
    BoundaryHandler* handler;
    LinkedCellContainer reflectiveContainer;
    LinkedCellContainer periodicContainer;
    void SetUp() override {
        auto r = boundary_type::value::reflective;
        auto reflectiveDomain = domain_type(double_vector(9, 9, 9), 3,
                                            boundaries_type(r, r, r, r, r, r));
        auto p = Particle({4.5,4.5,4.5},{0,0,0},1,5.0,1.0);
        auto pc = ParticleContainer();
        reflectiveContainer = LinkedCellContainer(reflectiveDomain, pc);
        reflectiveContainer.getParticles().push(p);


        auto q = boundary_type::value::periodic;
        auto periodicDomain = domain_type(double_vector(9, 9, 9), 3,
                                          boundaries_type(q,q,q,q,q,q));
        periodicContainer = LinkedCellContainer(periodicDomain, pc);
        periodicContainer.getParticles().push(p);
    }
};

/**
 * Checks if forced is applied correctly at border: left.
 */
TEST_F(BoundaryHandlerFixture, Reflect_Left){
    auto &p = reflectiveContainer.getParticles().getParticles().at(0);
    p.getX()[0] = 1;
    reflectiveContainer.assignParticle(p);
    auto bh = reflectiveContainer.getBoundaryHandler();
    bh->handle(&reflectiveContainer.getCells());
    EXPECT_NE(p.getF()[0], 0);
}

/**
 * Checks if forced is applied correctly at border: right.
 */
TEST_F(BoundaryHandlerFixture, Reflect_Right){
    auto &p = reflectiveContainer.getParticles().getParticles().at(0);
    p.getX()[0] = 8;
    reflectiveContainer.assignParticle(p);
    auto bh = reflectiveContainer.getBoundaryHandler();
    bh->handle(&reflectiveContainer.getCells());
    EXPECT_NE(p.getF()[0], 0);
}

/**
 * Checks if forced is applied correctly at border: top.
 */
TEST_F(BoundaryHandlerFixture, Reflect_Top){
    auto &p = reflectiveContainer.getParticles().getParticles().at(0);
    p.getX()[1] = 8;
    reflectiveContainer.assignParticle(p);
    auto bh = reflectiveContainer.getBoundaryHandler();
    bh->handle(&reflectiveContainer.getCells());
    EXPECT_NE(p.getF()[1], 0);
}

/**
 * Checks if forced is applied correctly at border: bottom.
 */
TEST_F(BoundaryHandlerFixture, Reflect_Bottom){
    auto &p = reflectiveContainer.getParticles().getParticles().at(0);
    p.getX()[1] = 1;
    reflectiveContainer.assignParticle(p);
    auto bh = reflectiveContainer.getBoundaryHandler();
    bh->handle(&reflectiveContainer.getCells());
    EXPECT_NE(p.getF()[1], 0);
}


/**
 * Checks if forced is applied correctly at border: front.
 */
TEST_F(BoundaryHandlerFixture, Reflect_Front){
    auto &p = reflectiveContainer.getParticles().getParticles().at(0);
    p.getX()[2] = 1;
    reflectiveContainer.assignParticle(p);
    auto bh = reflectiveContainer.getBoundaryHandler();
    bh->handle(&reflectiveContainer.getCells());
    EXPECT_NE(p.getF()[2], 0);
}

/**
 * Checks if forced is applied correctly at border: back.
 */
TEST_F(BoundaryHandlerFixture, Reflect_Back){
    auto &p = reflectiveContainer.getParticles().getParticles().at(0);
    p.getX()[2] = 8;
    reflectiveContainer.assignParticle(p);
    auto bh = reflectiveContainer.getBoundaryHandler();
    bh->handle(&reflectiveContainer.getCells());
    EXPECT_NE(p.getF()[2], 0);
}

/**
 * Checks if forced is applied correctly when not at border.
 */
TEST_F(BoundaryHandlerFixture, NotOnBorder){
    auto &p = reflectiveContainer.getParticles().getParticles().at(0);
    auto bh = reflectiveContainer.getBoundaryHandler();
    bh->handle(&reflectiveContainer.getCells());
    EXPECT_DOUBLE_EQ(p.getF()[0], 0);
    EXPECT_DOUBLE_EQ(p.getF()[1], 0);
    EXPECT_DOUBLE_EQ(p.getF()[2], 0);
}

/**
 * Checks if particle is periodically shifted on border: left.
 */
TEST_F(BoundaryHandlerFixture, Period_Left){
    auto &p = periodicContainer.getParticles().getParticles().at(0);
    p.getX()[0] = 1;
    periodicContainer.assignParticle(p);
    p.getX()[0] = -1;
    auto bh = periodicContainer.getBoundaryHandler();
    bh->handle(&periodicContainer.getCells());
    EXPECT_DOUBLE_EQ(p.getX()[0], periodicContainer.getDomainSize()[0] - 1);
}

/**
 * Checks if particle is periodically shifted on border: left.
 */
TEST_F(BoundaryHandlerFixture, Period_Right){
    auto &p = periodicContainer.getParticles().getParticles().at(0);
    p.getX()[0] = 8;
    periodicContainer.assignParticle(p);
    p.getX()[0] = 10;
    auto bh = periodicContainer.getBoundaryHandler();
    bh->handle(&periodicContainer.getCells());
    EXPECT_DOUBLE_EQ(p.getX()[0], 1);
}

/**
 * Checks if particle is periodically shifted on border: bottom.
 */
TEST_F(BoundaryHandlerFixture, Period_Bottom){
    auto &p = periodicContainer.getParticles().getParticles().at(0);
    p.getX()[1] = 1;
    periodicContainer.assignParticle(p);
    p.getX()[1] = -1;
    auto bh = periodicContainer.getBoundaryHandler();
    bh->handle(&periodicContainer.getCells());
    EXPECT_DOUBLE_EQ(p.getX()[1], periodicContainer.getDomainSize()[1] - 1);
}

/**
 * Checks if particle is periodically shifted on border: top.
 */
TEST_F(BoundaryHandlerFixture, Period_Top){
    auto &p = periodicContainer.getParticles().getParticles().at(0);
    p.getX()[1] = 8;
    periodicContainer.assignParticle(p);
    p.getX()[1] = 10;
    auto bh = periodicContainer.getBoundaryHandler();
    bh->handle(&periodicContainer.getCells());
    EXPECT_DOUBLE_EQ(p.getX()[1], 1);
}

/**
 * Checks if particle is periodically shifted on border: front.
 */
TEST_F(BoundaryHandlerFixture, Period_Front){
    auto &p = periodicContainer.getParticles().getParticles().at(0);
    p.getX()[2] = 1;
    periodicContainer.assignParticle(p);
    p.getX()[2] = -1;
    auto bh = periodicContainer.getBoundaryHandler();
    bh->handle(&periodicContainer.getCells());
    EXPECT_DOUBLE_EQ(p.getX()[2], periodicContainer.getDomainSize()[2] - 1);
}

/**
 * Checks if particle is periodically shifted on border: back.
 */
TEST_F(BoundaryHandlerFixture, Period_Back){
    auto &p = periodicContainer.getParticles().getParticles().at(0);
    p.getX()[2] = 8;
    periodicContainer.assignParticle(p);
    p.getX()[2] = 10;
    auto bh = periodicContainer.getBoundaryHandler();
    bh->handle(&periodicContainer.getCells());
    EXPECT_DOUBLE_EQ(p.getX()[2], 1);
}

/**
 * Checks if periodic neighbours are added correctly.
 */
TEST_F(BoundaryHandlerFixture, Periodic_Neighbours){
    auto &cells = periodicContainer.getCells();
    auto c000 = cells.at(0);
    auto c222 = cells.at(periodicContainer.getIndex({2,2,2}));
    auto c200 = cells.at(periodicContainer.getIndex({2,0,0}));
    EXPECT_TRUE(c000.isNeighbour(c222));
    EXPECT_TRUE(c222.isNeighbour(c000));
    EXPECT_TRUE(c000.isNeighbour(c200));
    EXPECT_TRUE(c200.isNeighbour(c000));
    EXPECT_EQ(c000.getNeighbors().size(), 26);

    auto c011 = cells.at(periodicContainer.getIndex({0,1,1}));
    EXPECT_EQ(c000.getNeighbors().size(), 26);

    auto c001 = cells.at(periodicContainer.getIndex({0,0,1}));
    EXPECT_EQ(c000.getNeighbors().size(), 26);
}