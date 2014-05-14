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

const char* PiParser::parseData(PiHeader &header, std::string &data, int dataLength) {
	CustomParserWrapper dummyWrapper = CustomParserWrapper(header.parserid());
	CustomParserWrapper wrapper = _parserSet.find(dummyWrapper);
	if (wrapper == NULL) {
		return std::string();
	}
	const char *response;
	response = wrapper.parser.parse(data.c_str(), header);

	return response;
}

