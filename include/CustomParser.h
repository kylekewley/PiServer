#ifndef Custom_Parser_h
#define Custom_Parser_h

#include "PiErrorMessage.h"
#include "Constants.h"

class CustomParser {
public:
	CustomParser() {};
    virtual ~CustomParser() {};
	virtual PiMessage parse(std::vector<char>, int) {return PiErrorMessage(kUnimplementedParser); };
    
    virtual CustomParser* clone() const = 0;
};

#endif