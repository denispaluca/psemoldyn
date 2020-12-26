//
// Created by denis on 17.12.20.
//

#include <gtest/gtest.h>
#include <cell/LinkedCellContainer.h>

class BoundaryHandlerFixture : public testing::Test {
protected:
    BoundaryHandler* handler;
    LinkedCellContainer lcc;
    ParticleContainer pc;
    void SetUp() override {
        auto r = boundary_type::value::reflective;
        boundaries_type boundaries = boundaries_type(r,r,r,r,r,r);
        domain_type domain = domain_type(double_vector(9,9,9),3, boundaries);
        Particle p = Particle({4.5,4.5,4.5},{0,0,0},1,0);
        pc = ParticleContainer();
        lcc = LinkedCellContainer(domain, pc);
        lcc.getParticles().push(p);
    }
};

/**
 * Checks if forced is applied correctly at border: left.
 */
TEST_F(BoundaryHandlerFixture, left){
    auto &p = lcc.getParticles().getParticles().at(0);
    p.getX()[0] = 1;
    lcc.assignParticle(p);
    auto bh = lcc.getBoundaryHandler();
    bh->handle(&lcc.getCells());
    EXPECT_NE(p.getF()[0], 0);
}

/**
 * Checks if forced is applied correctly at border: right.
 */
TEST_F(BoundaryHandlerFixture, right){
    auto &p = lcc.getParticles().getParticles().at(0);
    p.getX()[0] = 8;
    lcc.assignParticle(p);
    auto bh = lcc.getBoundaryHandler();
    bh->handle(&lcc.getCells());
    EXPECT_NE(p.getF()[0], 0);
}

/**
 * Checks if forced is applied correctly at border: top.
 */
TEST_F(BoundaryHandlerFixture, top){
    auto &p = lcc.getParticles().getParticles().at(0);
    p.getX()[1] = 8;
    lcc.assignParticle(p);
    auto bh = lcc.getBoundaryHandler();
    bh->handle(&lcc.getCells());
    EXPECT_NE(p.getF()[1], 0);
}

/**
 * Checks if forced is applied correctly at border: bottom.
 */
TEST_F(BoundaryHandlerFixture, bottom){
    auto &p = lcc.getParticles().getParticles().at(0);
    p.getX()[1] = 1;
    lcc.assignParticle(p);
    auto bh = lcc.getBoundaryHandler();
    bh->handle(&lcc.getCells());
    EXPECT_NE(p.getF()[1], 0);
}


/**
 * Checks if forced is applied correctly at border: front.
 */
TEST_F(BoundaryHandlerFixture, front){
    auto &p = lcc.getParticles().getParticles().at(0);
    p.getX()[2] = 1;
    lcc.assignParticle(p);
    auto bh = lcc.getBoundaryHandler();
    bh->handle(&lcc.getCells());
    EXPECT_NE(p.getF()[2], 0);
}

/**
 * Checks if forced is applied correctly at border: back.
 */
TEST_F(BoundaryHandlerFixture, back){
    auto &p = lcc.getParticles().getParticles().at(0);
    p.getX()[2] = 8;
    lcc.assignParticle(p);
    auto bh = lcc.getBoundaryHandler();
    bh->handle(&lcc.getCells());
    EXPECT_NE(p.getF()[2], 0);
}

/**
 * Checks if forced is applied correctly when not at border.
 */
TEST_F(BoundaryHandlerFixture, NotOnBorder){
    auto &p = lcc.getParticles().getParticles().at(0);
    auto bh = lcc.getBoundaryHandler();
    bh->handle(&lcc.getCells());
    EXPECT_DOUBLE_EQ(p.getF()[0], 0);
    EXPECT_DOUBLE_EQ(p.getF()[1], 0);
    EXPECT_DOUBLE_EQ(p.getF()[2], 0);
}