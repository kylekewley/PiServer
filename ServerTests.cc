#include "PiServer.h"


#define PORT_NUMBER     10102
using namespace std;

int main(int argc, char **argv) {

    PiServer piServer = PiServer(PORT_NUMBER);
    return 0;
}
