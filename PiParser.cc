#include "PiParser.h"
#include "PiErrorMessage.h"
#include "PiHeader.pb.h"

PiParser& PiParser::getInstance() {
	static PiParser sharedInstance;

	return sharedInstance;
}

PiParser::PiParser() {

}

bool PiParser::registerParserForID(CustomParser *parser, int functionIDStart, int functionIDEnd) {
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

PiMessage PiParser::parseData(PiHeader &header, std::vector<char> data) {
    
    PiMessage response;
    
	CustomParserWrapper dummyWrapper = CustomParserWrapper(header.parserid());
	auto iterator = _parserSet.find(dummyWrapper);
	if (iterator == _parserSet.end()) {
        if (header.successresponse()) {
            response = PiErrorMessage(kNoParserFound); //No parser found
        }else {
            return PiMessage(); //Return an empty PiMessage (It wont get sent)
        }
        
        
	}
    CustomParserWrapper wrapper = *iterator;
	
    
    try {
        response = wrapper.parser->parse(data);
        
        if (response.isEmpty && header.successresponse()) {
            //Just send a header back
            
            response = PiMessage(0);
        }
        
    } catch (exception e) {
        //Send an error message
        response = PiErrorMessage(kParserRuntimeException);
    }
    response.messageHeader.set_messageid(header.messageid());
    
    return response;
}

