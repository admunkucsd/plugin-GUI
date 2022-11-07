//
//  TestRunner.hpp
//  ALL_BUILD
//
//  Created by Allen Munk on 11/7/22.
//

#ifndef TestRunner_h
#define TestRunner_h

#include <stdio.h>
#include "Core/DataBufferTests.h"

class TestRunner {
public:
    TestRunner();
    ~TestRunner();
private:
    static DataBufferResizeTest dataBufferResizeTest;
};

#endif /* TestRunner_h */
