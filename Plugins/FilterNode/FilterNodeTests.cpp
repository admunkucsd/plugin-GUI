//
//  FilterNode_Tests.cpp
//  FilterNode_tests
//
//  Created by Allen Munk on 3/15/23.
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "FilterNode.h"

class FilterNodeTests : public ::testing::Test {
 protected:
    FilterNodeTests() {
    }

    ~FilterNodeTests() override {
    }

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST(FilterNodeTest, ContructorTest) {
    FilterNode* uut = new FilterNode();
    
    ASSERT_EQ(uut -> getDisplayName(), "Bandpass Filter");
    
    delete uut;
}

