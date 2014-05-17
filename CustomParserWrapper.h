#ifndef Custom_Parser_Wrapper_h
#define Custom_Parser_Wrapper_h

#include "Constants.h"
#include "CustomParser.h"

class CustomParserWrapper {
public:
	/**
	*The range of message IDs to parse
	*/
	Range range;
	
	/**
	*The object used to parse the the ParserMessage
	*/
	CustomParser *parser;

	CustomParserWrapper(Range r, CustomParser *p): range(r), parser(p) {};
	CustomParserWrapper(int parserID): range(Range(parserID, parserID)) {};
};

struct ParserWrapperCompare
{
	bool operator()(const CustomParserWrapper& lhv, const CustomParserWrapper& rhv) const {return lhv.range.second < rhv.range.first;}
};
#endif