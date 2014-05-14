#include "CustomBufferParser.h"

using namespace std;

CustomBufferParser::~CustomBufferParser() {
	delete inputMessage;
}
const char* CustomBufferParser::parse(const char *data, PiHeader &header) {
	inputMessage->ParseFromArray(data, header.messagelength());
	ProtocolBuffer &output = parse(inputMessage, header);

	string serializedString;
	output.SerializeToString(&serializedString);


	return serializedString.c_str();
}