#include "PiServer.h"
#include "PiParser.h"

#define PORT_NUMBER     10002
using namespace std;

char* binaryParser(char *data, int dataLength, PiHeader header) {
	return NULL;
}

int main(int argc, char **argv) {
    
    PiServer piServer = PiServer(PORT_NUMBER);

    return 0;
}
