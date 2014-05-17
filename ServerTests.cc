#include "PiServer.h"
#include "PiParser.h"
#include "TestParser.h"
#include "CustomBufferParser.h"

#define PORT_NUMBER     10102
using namespace std;

char* binaryParser(char *data, int dataLength, PiHeader header) {
	return NULL;
}

int main(int argc, char **argv) {
    
    PiParser::getInstance().registerParserForID(new TestParser(), 1, 1);
    PiServer piServer = PiServer(PORT_NUMBER);

    return 0;
}
