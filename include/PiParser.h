#ifndef Pi_Parser_h
#define Pi_Parser_h

#include "CustomParserWrapper.h"
#include <set>

class PiHeader;

class PiParser
{
public:
    PiParser();
	
    bool registerParserForID(CustomParser *parser, int functionIDStart, int functionIDEnd);

	PiMessage parseData(PiHeader &header, std::vector<char> data, int clientID);

	/**
	*data is prefixed with a 
	*/
	int getHeaderLengthPrefix(char *data);
private:

	bool parserRangeValid(CustomParserWrapper &wrapper);
	std::set<CustomParserWrapper, ParserWrapperCompare> _parserSet;
};

#endif