//
//  DataBufferTests.cpp
//  open-ephys
//
//  Created by Allen Munk on 11/7/22.
//

#include "DataBufferTests.h"

const int channels1 = 1024;
const int channels2 = 4096;
const int dataSize = sizeof(float);
void DataBufferResizeTest::runTest() {
    dataBuffer = new DataBuffer(channels1, channels1*dataSize);
    beginTest("Data Buffer Resizing from 1024 to 4096 Channels");
    expectEquals(dataBuffer -> getNumChans(), channels1);
    dataBuffer->resize(channels2, channels2 * dataSize);
    expectNotEquals(dataBuffer -> getNumChans(), channels1);
    expectEquals(dataBuffer -> getNumChans(), channels2);
    delete dataBuffer;
}
