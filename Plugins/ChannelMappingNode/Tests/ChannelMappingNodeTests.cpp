#include <stdio.h>

#include "gtest/gtest.h"

#include "../ChannelMappingNode.h"
#include <ProcessorHeaders.h>
#include <ModelProcessors.h>
#include <ModelApplication.h>
#include <TestFixtures.h>

class ChannelMappingNodeTests : public ProcessorTest {
protected:
    ChannelMappingNodeTests() : ProcessorTest(1, 150) {
    }

    ~ChannelMappingNodeTests() override {
    }

    void SetUp() override {
        ProcessorTest::SetUp();
    }

    void TearDown() override {
        ProcessorTest::TearDown();

    }

};


