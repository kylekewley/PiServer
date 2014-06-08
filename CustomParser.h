#ifndef Custom_Parser_h
#define Custom_Parser_h

#include "PiMessage.h"

class CustomParser {
public:
	CustomParser() {};
	virtual PiMessage parse(std::vector<char> data, unsigned long messageID) {return PiMessage(kParserNotFoundID, messageID); };
};

#endif