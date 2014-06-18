#ifndef Custom_Parser_Wrapper_h
#define Custom_Parser_Wrapper_h

#include "CustomParser.h"
#include "Constants.h"

class CustomParserWrapper {
public:
	/**
	*The range of message IDs to parse
	*/
	const Range range;
	
	/**
	*The object used to parse the the ParserMessage
	*/
    std::shared_ptr<CustomParser> parser;
    
	CustomParserWrapper(Range r, std::shared_ptr<CustomParser> &p);
    
	CustomParserWrapper(int parserID);
    
};

struct ParserWrapperCompare
{
	bool operator()(const CustomParserWrapper& lhv, const CustomParserWrapper& rhv) const {return lhv.range.second < rhv.range.first;}
};
#endif