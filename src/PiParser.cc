#include "PiParser.h"
#include "PiErrorMessage.h"
#include "PiHeader.pb.h"


PiParser::PiParser() {

}

PiParser::~PiParser() {
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

PiMessage PiParser::parseData(PiHeader &header, std::vector<char> data, int clientID) {
    
    PiMessage response;
    
	CustomParserWrapper dummyWrapper = CustomParserWrapper(header.parserid());
	std::set<CustomParserWrapper>::iterator iterator = _parserSet.find(dummyWrapper);
	if (iterator == _parserSet.end()) {
        if (header.successresponse()) {
            response = PiErrorMessage(kNoParserFound); //No parser found
        }else {
            response = PiMessage(); //Return an empty PiMessage (It wont get sent)
        }
        response.messageHeader.set_messageid(header.messageid());

        return response;
	}
    
    //We know we have a valid parser now
	
    
    try {
        response = iterator->parser->parse(data, clientID);
        
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

