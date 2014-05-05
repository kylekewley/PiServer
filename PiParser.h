#ifndef Pi_Parser_h
#define Pi_Parser_h

#include "Constants.h"
#include "CustomBufferParser.h"
#include "CustomParserWrapper.h"
#include "TestParser.h"
#include <set>


class PiParser
{
public:
	static PiParser& getInstance();


	bool registerParserForID(CustomParser &parser, int functionIDStart, int functionIDEnd);

	char* parseData(char *data, int dataLength);

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