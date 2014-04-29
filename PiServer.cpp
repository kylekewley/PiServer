#include "PiServer.h"

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>


#include <unistd.h>




using namespace std;

PiServer::PiServer(int port): _port(port) {
}

void PiServer::connectToPort(char *port) {
	//Figure out where to bind
	struct addrinfo hints, *ai, *p;

	//Clear the struct out
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (int error = getaddrinfo(NULL, port, &hints, &ai) != 0) {
		//There was and error getting the address info
		string errorString = "getaddrinfo failed with error number " + to_string(error); 
		throw runtime_error(errorString);
	}

	int socketfd;
	//Loop through each returned addrinfo struct in the linked list
	for (p = ai; p != NULL; p = p->ai_next) {
		socketfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

		if (socketfd < 0)
			continue; //Skip

		//prevent "address already in use" error message
		int yes = 1;
		setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		//try to bind
		if (::bind(socketfd, p->ai_addr, p->ai_addrlen) == -1) {
			//Failed to bind. Try the next one
			close(socketfd);
			continue;
		}

		//Successfully bound to a socket
		break; 
	}

	if (p == NULL) { 
		//Got to the end of the linked list without binding to a socket
		string errorString = "PiServer failed to bind to socket. ";
		throw runtime_error(errorString);
	}

	freeaddrinfo(ai); // all done with this
}

void PiServer::listenForClients() {


}