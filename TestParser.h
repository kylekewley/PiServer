#ifndef Test_Parser_h
#define Test_Parser_h

#include "Constants.h"
#include "CustomBufferParser.h"


class TestParser : public CustomBufferParser {
public:
	TestParser();
	ProtocolBuffer &parse(ProtocolBuffer *data, PiHeader &header);
};
#endif