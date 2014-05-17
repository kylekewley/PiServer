#ifndef Test_Parser_h
#define Test_Parser_h

#include "Constants.h"
#include "CustomBufferParser.imp.h"
class TestMessage;

class TestParser : public CustomBufferParser<TestMessage> {
public:
	TestParser();
	ProtocolBuffer *parseBuffer(const TestMessage *data);
};
#endif