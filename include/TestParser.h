#ifndef Test_Parser_h
#define Test_Parser_h

#include "CustomBufferParser.imp.h"
#include "TestMessage.pb.h"

class TestMessage;

class TestParser : public CustomBufferParser<TestMessage> {
public:
	TestParser();
    
	ProtocolBuffer *parseBuffer(const TestMessage *data, int clientID) const;

};
#endif