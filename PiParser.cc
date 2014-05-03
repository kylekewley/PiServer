#include "PiParser.h"
#include <map>

PiParser& PiParser::getInstance() {
	static PiParser sharedInstance;

	return sharedInstance;
}

PiParser::PiParser() {

}

template <class T, class E> bool PiParser::registerParserForID(E(*parseData)(T data, PiHeader header), int functionID) {
	return false;
}
bool PiParser::registerBinaryParserForID(char*(*binaryParser)(char *data, PiHeader header), int functionID) {
	return false;
}