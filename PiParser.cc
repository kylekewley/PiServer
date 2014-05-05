#include "PiParser.h"
#include "PiHeader.pb.h"
#include "CustomParserWrapper.h"
PiParser& PiParser::getInstance() {
	static PiParser sharedInstance;

	return sharedInstance;
}

PiParser::PiParser() {

}

bool PiParser::registerParserForID(CustomParser &parser, int functionIDStart, int functionIDEnd) {
	//Wrap the parser

	Range r = Range(functionIDStart, functionIDEnd);
	CustomParserWrapper wrapper = CustomParserWrapper(r, parser);
	
	if (!parserRangeValid(wrapper)) {
		return false;
	}

	_parserSet.insert(wrapper);
	return true;
}


bool PiParser::parserRangeValid(CustomParserWrapper &wrapper) {
	return _parserSet.find(wrapper) == _parserSet.end();
}

char* PiParser::parseData(char *data, int dataLength) {
	//Start by parsing a PiHeader
	return NULL;
}

