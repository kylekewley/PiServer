#ifndef Custom_Parser_h
#define Custom_Parser_h

#include "PiErrorMessage.h"
#include "Constants.h"

class CustomParser {
public:
	CustomParser() {};
	virtual PiMessage parse(std::vector<char> data) {return PiErrorMessage(kUnimplementedParser); };
};

#endif