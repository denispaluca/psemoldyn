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
                                            boundaries_type(r, r, r, r, r, r), double_vector(0,0,0), false);
        auto p = Particle({4.5,4.5,4.5},{0,0,0},1,5.0,1.0);
        auto pc = ParticleContainer();
        reflectiveContainer = LinkedCellContainer(reflectiveDomain, pc);
        reflectiveContainer.getParticles().push(p);


        auto q = boundary_type::value::periodic;
        auto periodicDomain = domain_type(double_vector(9, 9, 9), 3,
                                          boundaries_type(q,q,q,q,q,q),
                                          double_vector(0,0,0), false);
        periodicContainer = LinkedCellContainer(periodicDomain, pc);
        periodicContainer.getParticles().push(p);
    }
};

/**
 * Checks if forced is applied correctly at border: left.
 */
TEST_F(BoundaryHandlerFixture, Reflect_Left){
    auto &p = reflectiveContainer.getParticles().getParticles().at(0);
    p.x[0] = 1;
    reflectiveContainer.assignParticle(p);
    auto bh = reflectiveContainer.getBoundaryHandler();
    bh->handle(&reflectiveContainer.getCells());
    EXPECT_NE(p.f[0], 0);
}

/**
 * Checks if forced is applied correctly at border: right.
 */
TEST_F(BoundaryHandlerFixture, Reflect_Right){
    auto &p = reflectiveContainer.getParticles().getParticles().at(0);
    p.x[0] = 8;
    reflectiveContainer.assignParticle(p);
    auto bh = reflectiveContainer.getBoundaryHandler();
    bh->handle(&reflectiveContainer.getCells());
    EXPECT_NE(p.f[0], 0);
}

/**
 * Checks if forced is applied correctly at border: top.
 */
TEST_F(BoundaryHandlerFixture, Reflect_Top){
    auto &p = reflectiveContainer.getParticles().getParticles().at(0);
    p.x[1] = 8;
    reflectiveContainer.assignParticle(p);
    auto bh = reflectiveContainer.getBoundaryHandler();
    bh->handle(&reflectiveContainer.getCells());
    EXPECT_NE(p.f[1], 0);
}

/**
 * Checks if forced is applied correctly at border: bottom.
 */
TEST_F(BoundaryHandlerFixture, Reflect_Bottom){
    auto &p = reflectiveContainer.getParticles().getParticles().at(0);
    p.x[1] = 1;
    reflectiveContainer.assignParticle(p);
    auto bh = reflectiveContainer.getBoundaryHandler();
    bh->handle(&reflectiveContainer.getCells());
    EXPECT_NE(p.f[1], 0);
}


/**
 * Checks if forced is applied correctly at border: front.
 */
TEST_F(BoundaryHandlerFixture, Reflect_Front){
    auto &p = reflectiveContainer.getParticles().getParticles().at(0);
    p.x[2] = 1;
    reflectiveContainer.assignParticle(p);
    auto bh = reflectiveContainer.getBoundaryHandler();
    bh->handle(&reflectiveContainer.getCells());
    EXPECT_NE(p.f[2], 0);
}

/**
 * Checks if forced is applied correctly at border: back.
 */
TEST_F(BoundaryHandlerFixture, Reflect_Back){
    auto &p = reflectiveContainer.getParticles().getParticles().at(0);
    p.x[2] = 8;
    reflectiveContainer.assignParticle(p);
    auto bh = reflectiveContainer.getBoundaryHandler();
    bh->handle(&reflectiveContainer.getCells());
    EXPECT_NE(p.f[2], 0);
}

/**
 * Checks if forced is applied correctly when not at border.
 */
TEST_F(BoundaryHandlerFixture, NotOnBorder){
    auto &p = reflectiveContainer.getParticles().getParticles().at(0);
    auto bh = reflectiveContainer.getBoundaryHandler();
    bh->handle(&reflectiveContainer.getCells());
    EXPECT_DOUBLE_EQ(p.f[0], 0);
    EXPECT_DOUBLE_EQ(p.f[1], 0);
    EXPECT_DOUBLE_EQ(p.f[2], 0);
}

/**
 * Checks if particle is periodically shifted on border: left.
 */
TEST_F(BoundaryHandlerFixture, Period_Left){
    auto &p = periodicContainer.getParticles().getParticles().at(0);
    p.x[0] = 1;
    periodicContainer.assignParticle(p);
    p.x[0] = -1;
    auto bh = periodicContainer.getBoundaryHandler();
    bh->handle(&periodicContainer.getCells());
    EXPECT_DOUBLE_EQ(p.x[0], periodicContainer.getDomainSize()[0] - 1);
}

/**
 * Checks if particle is periodically shifted on border: left.
 */
TEST_F(BoundaryHandlerFixture, Period_Right){
    auto &p = periodicContainer.getParticles().getParticles().at(0);
    p.x[0] = 8;
    periodicContainer.assignParticle(p);
    p.x[0] = 10;
    auto bh = periodicContainer.getBoundaryHandler();
    bh->handle(&periodicContainer.getCells());
    EXPECT_DOUBLE_EQ(p.x[0], 1);
}

/**
 * Checks if particle is periodically shifted on border: bottom.
 */
TEST_F(BoundaryHandlerFixture, Period_Bottom){
    auto &p = periodicContainer.getParticles().getParticles().at(0);
    p.x[1] = 1;
    periodicContainer.assignParticle(p);
    p.x[1] = -1;
    auto bh = periodicContainer.getBoundaryHandler();
    bh->handle(&periodicContainer.getCells());
    EXPECT_DOUBLE_EQ(p.x[1], periodicContainer.getDomainSize()[1] - 1);
}

/**
 * Checks if particle is periodically shifted on border: top.
 */
TEST_F(BoundaryHandlerFixture, Period_Top){
    auto &p = periodicContainer.getParticles().getParticles().at(0);
    p.x[1] = 8;
    periodicContainer.assignParticle(p);
    p.x[1] = 10;
    auto bh = periodicContainer.getBoundaryHandler();
    bh->handle(&periodicContainer.getCells());
    EXPECT_DOUBLE_EQ(p.x[1], 1);
}

/**
 * Checks if particle is periodically shifted on border: front.
 */
TEST_F(BoundaryHandlerFixture, Period_Front){
    auto &p = periodicContainer.getParticles().getParticles().at(0);
    p.x[2] = 1;
    periodicContainer.assignParticle(p);
    p.x[2] = -1;
    auto bh = periodicContainer.getBoundaryHandler();
    bh->handle(&periodicContainer.getCells());
    EXPECT_DOUBLE_EQ(p.x[2], periodicContainer.getDomainSize()[2] - 1);
}

/**
 * Checks if particle is periodically shifted on border: back.
 */
TEST_F(BoundaryHandlerFixture, Period_Back){
    auto &p = periodicContainer.getParticles().getParticles().at(0);
    p.x[2] = 8;
    periodicContainer.assignParticle(p);
    p.x[2] = 10;
    auto bh = periodicContainer.getBoundaryHandler();
    bh->handle(&periodicContainer.getCells());
    EXPECT_DOUBLE_EQ(p.x[2], 1);
}
