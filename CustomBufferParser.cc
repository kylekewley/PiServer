#include "CustomBufferParser.h"

using namespace std;

CustomBufferParser::~CustomBufferParser() {
	delete inputMessage;
}
std::vector<char> CustomBufferParser::parse(std::vector<char> data, PiHeader &header) {
	inputMessage->ParseFromArray(data.data(), header.messagelength());
	ProtocolBuffer &output = parse(inputMessage, header);

    //Create a vector the size of output
    std::vector<char> vector = std::vector<char>(output.ByteSize());
	output.SerializeToArray(vector.data(), vector.size());


	return vector;
}