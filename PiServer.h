#ifndef Pi_Server_h
#define Pi_Server_h

#include <iostream>
#include "ClientManager.h"

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
     *The messageQueue holds outgoing messages based on each connection's socketfd
     */
    vector<vector<char>> messageQueue;
    /**
    *Manages the status of client connections and messages
    */
    ClientManager _clientManager;
    /**
    *This is a method used to create a tcp connection.
    *This method binds to a port, then calls listenForClients(),
    *which blocks the thread and requests replies to messages
    *via the PiParser singleton class
    */
    void connectToPort(const char *port);

    /**
    *Wait to accept new client connections. Manage client messages
    *and send replies back using the PiParser singleton
    */
    void listenForClients(int serverfd);

    /**
    *
    *@return    The file descriptor for the new client or -1 if there was an error
    */
    int connectToClient(int serverfd, fd_set *masterfds, int *maxfd);

    /**
    *Gets the IP address from a new client connection
    */
    void *getInternetAddress(struct sockaddr *sa);
};

#endif
