#ifndef Test_Parser_h
#define Test_Parser_h

#include "CustomBufferParser.imp.h"
#include "Constants.h"

class TestMessage;

class TestParser : public CustomBufferParser<TestMessage> {
public:
	TestParser();
    
    TestParser(const TestParser& testParser);
    
	ProtocolBuffer *parseBuffer(const TestMessage *data, int clientID);
    
    TestParser* clone() const;
};
#endif