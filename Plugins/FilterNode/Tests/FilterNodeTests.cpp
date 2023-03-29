//
//  FilterNode_Tests.cpp
//  FilterNode_tests
//
//  Created by Allen Munk on 3/15/23.
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "../FilterNode.h"
#include <ProcessorHeaders.h>
#include <ModelProcessors.h>
#include <ModelApplication.h>

//class FilterNodeTests : public ::testing::Test {
//protected:
//    FilterNodeTests() {
//    }
//
//    ~FilterNodeTests() override {
//    }
//
//    void SetUp() override {
//
//    }
//
//    void TearDown() override {
//
//    }
//
//};


TEST(FilterNodeTest, ContructorTest) {
    FilterNode* uut = new FilterNode();
    FakeSourceNode* fake = new FakeSourceNode();
    StubAccessClass* sAC = new StubAccessClass();
    sAC->addMessageCenter();
    fake->addTestDataStreams();
    fake->update();
    
    uut->setSourceNode(fake);
    uut->update();
    
    ASSERT_EQ(uut -> getDisplayName(), "Bandpass Filter");
    delete uut;
    delete fake;
    delete sAC;
}

//TEST(FilterNodeTest, ProcessTets) {
//    FilterNode* uut = new FilterNode();
//    
//    ASSERT_EQ(uut -> getDisplayName(), "Bandpass Filter");
//    
//    delete uut;
//}
