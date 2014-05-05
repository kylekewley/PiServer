#ifndef Custom_Parser_h
#define Custom_Parser_h

#include "PiHeader.pb.h"

class CustomParser {
public:
	CustomParser() {};
	virtual const char* parse(const char *data, PiHeader &header) = 0;
};

#endif