//
//  FilterNode_Tests.cpp
//  FilterNode_tests
//
//  Created by Allen Munk on 3/15/23.
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "CommonAverageRef.h"

class CommonAverageRefTest : public ::testing::Test {
 protected:
    CommonAverageRefTest() {
    }

    ~CommonAverageRefTest() override {
    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};



TEST(CommonAverageRefTest, ContructorTest) {
    CommonAverageRef* uut = new CommonAverageRef();
    
    ASSERT_EQ(uut -> getDisplayName(), "Bandpass Filter");
    
    delete uut;
}

