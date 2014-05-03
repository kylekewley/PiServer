#include "PiHeader.pb.h"

class PiParser
{
public:
	static PiParser& getInstance();


	template <class T, class E> bool registerParserForID(E(*parseData)(T data, PiHeader header), int functionID);
	bool registerBinaryParserForID(char*(*binaryParser)(char *data, PiHeader header), int functionID);

	char* parseData(char *data, int length);
private:
	PiParser();
	PiParser(PiParser const&);              // Don't Implement
	void operator=(PiParser const&); // Don't implement


};