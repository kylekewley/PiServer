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

    // PiServer piServer = PiServer(PORT_NUMBER);
    PiParser &parser = PiParser::getInstance();
    TestParser tParser = TestParser();
    char *c;
    bool result = parser.registerParserForID(tParser, 0, 128);
    cout << "Result " << to_string(result) << endl;
    result = parser.registerParserForID(tParser, 100, 100);
    cout << "Result " << to_string(result) << endl;

    return 0;
}
