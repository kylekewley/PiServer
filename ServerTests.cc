#include "PiServer.h"

#define PORT_NUMBER     10002
using namespace std;

char* binaryParser(char *data, int dataLength, PiHeader header) {
	return NULL;
}

int main(int argc, char **argv) {
    
    while (true) {
        try {
            PiServer piServer = PiServer(PORT_NUMBER);
        } catch (exception e) {
            cerr << "PiServer crashed with exception: " << e.what() << endl;
        }

    }

    return 0;
}
