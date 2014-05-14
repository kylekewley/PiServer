#ifndef Custom_Parser_h
#define Custom_Parser_h

#include "PiHeader.pb.h"

class CustomParser {
public:
	CustomParser() {};
	virtual std::vector<char> parse(std::vector<char> data, PiHeader &header) {return std::vector<char>();};
};

#endif