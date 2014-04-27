#ifndef Pi_Server_h
#define Pi_Server_h

#include <iostream>
using namespace std;

class PiServer {
    public:
        /**
         *@desc Start a server listening on the specified port
         *@param    port    The port to listen for clients on
         */
        PiServer(int port);
    private:
        /**
         *The port the server is connecting to
         */
        int _port;
};

#endif
