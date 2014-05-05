#include "TestParser.h"
#include "PiHeader.pb.h"

TestParser::TestParser(): CustomBufferParser(new PiHeader()){

}

ProtocolBuffer& TestParser::parse(ProtocolBuffer *data, PiHeader &header) {

	return header;
}