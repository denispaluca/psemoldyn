//
// Created by denis on 17.12.20.
//

#include <gtest/gtest.h>
#include <cell/BoundaryHandler.h>

class BoundaryHandlerFixture : public testing::Test {
protected:
    BoundaryHandler* handler;
    boundary_type boundaries = boundary_type(true, true, true, true, true, true);
    void SetUp() override {
        handler = new BoundaryHandler(boundaries, {100, 100, 100});
    }
};

/**
 * Checks if forced is applied correctly at border: left.
 */
TEST_F(BoundaryHandlerFixture, left){
    Particle p = Particle({1,50,50},{0,0,0},1,0);
    handler->applyForce(p);
    EXPECT_NE(p.getF()[0], 0);
}

/**
 * Checks if forced is applied correctly at border: right.
 */
TEST_F(BoundaryHandlerFixture, right){
    Particle p = Particle({99,50,50},{0,0,0},1,0);
    handler->applyForce(p);
    EXPECT_NE(p.getF()[0], 0);
}

/**
 * Checks if forced is applied correctly at border: top.
 */
TEST_F(BoundaryHandlerFixture, top){
    Particle p = Particle({50,99,50},{0,0,0},1,0);
    handler->applyForce(p);
    EXPECT_NE(p.getF()[1], 0);
}

/**
 * Checks if forced is applied correctly at border: bottom.
 */
TEST_F(BoundaryHandlerFixture, bottom){
    Particle p = Particle({50,1,50},{0,0,0},1,0);
    handler->applyForce(p);
    EXPECT_NE(p.getF()[1], 0);
}


/**
 * Checks if forced is applied correctly at border: front.
 */
TEST_F(BoundaryHandlerFixture, front){
    Particle p = Particle({50,50,1},{0,0,0},1,0);
    handler->applyForce(p);
    EXPECT_NE(p.getF()[2], 0);
}

/**
 * Checks if forced is applied correctly at border: back.
 */
TEST_F(BoundaryHandlerFixture, back){
    Particle p = Particle({50,50,99},{0,0,0},1,0);
    handler->applyForce(p);
    EXPECT_NE(p.getF()[2], 0);
}

/**
 * Checks if forced is applied correctly when not at border.
 */
TEST_F(BoundaryHandlerFixture, NotOnBorder){
    Particle p = Particle({50,50,50},{0,0,0},1,0);
    handler->applyForce(p);
    EXPECT_DOUBLE_EQ(p.getF()[0], 0);
    EXPECT_DOUBLE_EQ(p.getF()[1], 0);
    EXPECT_DOUBLE_EQ(p.getF()[2], 0);
}