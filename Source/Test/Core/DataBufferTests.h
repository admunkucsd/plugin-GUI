//
//  DataBufferTests.hpp
//  open-ephys
//
//  Created by Allen Munk on 11/7/22.
//

#ifndef DataBufferTests_h
#define DataBufferTests_h

#include <stdio.h>
#include "../../Processors/DataThreads/DataBuffer.h"

class DataBuffer;

class DataBufferResizeTest : public UnitTest
{
public:
    /** Constructor*/
    DataBufferResizeTest() : UnitTest("Data Buffer Resize Test", "Core") {}

    /** Run the test */
    void runTest();

private:

    DataBuffer* dataBuffer;

};

#endif /* DataBufferTests_h */
