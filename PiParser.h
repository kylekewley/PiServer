#ifndef Pi_Parser_h
#define Pi_Parser_h

#include "Constants.h"
#include "CustomParserWrapper.h"
#include <set>

class PiHeader;

class PiParser
{
public:
	static PiParser& getInstance();


	bool registerParserForID(CustomParser *parser, int functionIDStart, int functionIDEnd);

	std::vector<char> parseData(PiHeader &header, std::vector<char> data);

	/**
	*data is prefixed with a 
	*/
	int getHeaderLengthPrefix(char *data);
private:
	PiParser();
	PiParser(PiParser const&);          // Don't Implement
	void operator=(PiParser const&); 	// Don't implement

	bool parserRangeValid(CustomParserWrapper &wrapper);
	std::set<CustomParserWrapper, ParserWrapperCompare> _parserSet;
};

#endif