#ifndef Custom_Parser_Wrapper_h
#define Custom_Parser_Wrapper_h

#include <utility>
#include "PiHeader.pb.h"
#include "Constants.h"
#include "CustomParser.h"
#include "TestParser.h"

class CustomParserWrapper {
public:
	/**
	*The range of message IDs to parse
	*/
	Range range;
	
	/**
	*The object used to parse the the ParserMessage
	*/
	CustomParser &parser;

	CustomParserWrapper(Range r, CustomParser &p): range(r), parser(p) {};
};

struct ParserWrapperCompare
{
	bool operator()(const CustomParserWrapper& lhv, const CustomParserWrapper& rhv) const {return lhv.range.second < rhv.range.first;}
};
#endif