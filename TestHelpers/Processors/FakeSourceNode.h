#ifndef FAKESOURCENODE_H
#define FAKESOURCENODE_H

#include <ProcessorHeaders.h>
#include <NonAPIHeaders.h>

class FakeSourceNode : public GenericProcessor {
public:
    FakeSourceNode();
    
    void addMessageChannel();
    void addTestDataStreams();
    
    void process(AudioBuffer<float>& continuousBuffer) override;
    
private:
};


#endif
