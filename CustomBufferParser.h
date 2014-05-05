#ifndef Custom_Buffer_Parser_h
#define Custom_Buffer_Parser_h

#include "Constants.h"
#include "CustomParser.h"

class CustomBufferParser : public CustomParser {
protected:
	ProtocolBuffer *inputMessage;
public:
	CustomBufferParser(ProtocolBuffer *inputMessage_): inputMessage(inputMessage_) {};
	const char* parse(const char *data, PiHeader &header);
	virtual ProtocolBuffer &parse(ProtocolBuffer *data, PiHeader &header) = 0;
	
};

#endif