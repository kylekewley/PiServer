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

        /**
        *This is a method used to create a tcp connection.
        *This method binds to a port, then calls listenForClients(),
        *which blocks the thread and requests replies to messages
        *via the PiParser singleton class
        */
        void connectToPort(char *port);

        /**
        *Wait to accept new client connections. Manage client messages
        *and send replies back using the PiParser singleton
        */
        void listenForClients();
};

#endif
