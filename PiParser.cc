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

std::vector<char> PiParser::parseData(PiHeader &header, std::vector<char> data) {
	CustomParserWrapper dummyWrapper = CustomParserWrapper(header.parserid());
	auto iterator = _parserSet.find(dummyWrapper);
	if (iterator == _parserSet.end()) {
		return std::vector<char>(); //No response
	}
    CustomParserWrapper wrapper = *iterator;
	std::vector<char> response = wrapper.parser.parse(data, header);

	return response;
}

