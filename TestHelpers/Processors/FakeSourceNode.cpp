#include "FakeSourceNode.h"

FakeSourceNode::FakeSourceNode() : GenericProcessor("Fake Source Node"){}

void FakeSourceNode::addMessageChannel() {
    
}

void FakeSourceNode::addTestDataStreams() {
    DataStream::Settings settings
    {
        "FakeSourceNode",
        "description",
        "identifier",
        20000
    };
    
    dataStreams.add(new DataStream(settings));
    
    for (int index= 0; index < 4; index++)
    {
        
        ContinuousChannel::Settings settings{
            ContinuousChannel::Type::ELECTRODE,
            "CH" + String(index),
            String(index),
            "identifier",
            
            1.0,
            
            dataStreams.getFirst()
        };
        
        continuousChannels.add(new ContinuousChannel(settings));
    }

}

void FakeSourceNode::process(AudioBuffer<float>& continuousBuffer) {}

