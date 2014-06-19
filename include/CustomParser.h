#ifndef Custom_Parser_h
#define Custom_Parser_h

#include "PiErrorMessage.h"
#include "Constants.h"
#include <iostream>
class CustomParser {
public:
	CustomParser() {};
    virtual ~CustomParser() {};
	virtual PiMessage parse(std::vector<char>, int) const {return PiErrorMessage(kUnimplementedParser); };
    
    
};

#endif
