#include "TestParser.h"
#include "PiHeader.pb.h"

//Pass in the type of protocol buffer to parse with
TestParser::TestParser(): CustomBufferParser(new PiHeader()){

}

ProtocolBuffer& TestParser::parse(ProtocolBuffer *data, PiHeader &header) {
	
	return header;
}