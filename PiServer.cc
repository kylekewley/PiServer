#include "PiServer.h"
#include "PiParser.h"

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <unistd.h>
#include <fcntl.h>

#include "PingParser.h"
#include "TestParser.h"


/**
*The number of pending client connections to allow
*before attempted connections recieve a Connection
*Refused error.
*/
static const int kClientBacklog = 10;
static const int kBufferSize = 8192;

using namespace std;

PiServer::PiServer(int port): _port(port) {
    //Add the default parsers
    registerDefaultParsers();
    
    //Start the server
	string portString = to_string(port);
	connectToPort(portString.c_str());
}

void PiServer::connectToPort(const char *port) {
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

	int serverfd;
	//Loop through each returned addrinfo struct in the linked list
	for (p = ai; p != NULL; p = p->ai_next) {
		serverfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        //Set to nonblocking
        fcntl(serverfd, F_SETFL, O_NONBLOCK);

		if (serverfd < 0)
			continue; //Skip

		//prevent "address already in use" error message
		int yes = 1;
		setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		//try to bind
		if (::bind(serverfd, p->ai_addr, p->ai_addrlen) == -1) {
			//Failed to bind. Try the next one
			close(serverfd);
			continue;
		}

		//Successfully bound to a socket. Stop trying to bind to others
		break;
	}

	if (p == NULL) { 
		//Got to the end of the linked list without binding to a socket
		throw runtime_error("PiServer failed to bind to socket.");
	}

	freeaddrinfo(ai); //Free our linked address info list

	//Mark the socket as ready to listen for incoming connections

	if (listen(serverfd, kClientBacklog) == -1) {
		//Error setting listen flag, wont listen for client connections
		throw runtime_error("Error setting socket listen flag");
	}
	//
	//Now we should be bound to a port and ready to listen for clients
	//
	cout << "PiServer is waiting for client connections on port " << to_string(_port) << "..." << endl;
	listenForClients(serverfd);
}

void PiServer::listenForClients(int serverfd) {
	/**
	*masterfd stores all open socket connections
	*readfd stores all sockets that have data to be read
	*writefd stores all sockets that can be written to
	*/
	fd_set masterfds, readfds, writefds;

	struct sockaddr_storage remoteaddr; // client address
    socklen_t addrlen;

    FD_ZERO(&masterfds);    // clear the master and temp sets
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);

    //Set the max file descriptor value
	int maxfd = serverfd;
	//Add serverfd to the master set
	FD_SET(serverfd, &masterfds);

	//Create a buffer for incoming messages
	char buffer[kBufferSize];
	//Loop forever listening for clients
	for(;;) {
		//nfds is the highest numbered file descriptor plus 1
		int nfds = maxfd + 1;

        readfds = masterfds; //We want to check if all sockets can be read and written to
        writefds = masterfds;

		if (select(nfds, &readfds, &writefds, NULL, NULL) == -1) {
			//There was an error with the select call
			throw runtime_error("Error in the socket select() call");
		}

		//Now the read_fds and write_fds are populated with readable and writable sockets
		//If serverfd is in read_fds, we have a new connection

		//Loop through each file descriptor and check whether they're readable
		for (int sockfd = 0; sockfd <= maxfd; ++sockfd) {
			if (FD_ISSET(sockfd, &readfds)) {
				//sockfd can be read
				if (sockfd == serverfd) {
					//We have a new connection
					cout << "Connecting to new client" << endl;
					connectToClient(serverfd, &masterfds, &maxfd);
				}else {
					//We have a message
					ssize_t length = recv(sockfd, buffer, kBufferSize, 0);

					if (length <= 0) {
						if (length == 0) {
							//sockfd hung up
							cout << "Socket " << to_string(sockfd) << " hung up" << endl;
						}else {
							//Error recieving data
							cerr << "Error recieving data" << endl;
						}
						//Close sockfd and remove from the master set
                        close(sockfd);
                        FD_CLR(sockfd, &masterfds);
					}else {
						//Read the message
						vector<char> response = _clientManager.receivedMessageOnPort(buffer, length, sockfd);
                        messageQueue[sockfd].insert(messageQueue[sockfd].end(), response.begin(), response.end());
					}
				}
			}
            if (FD_ISSET(sockfd, &masterfds) && sockfd != serverfd) {
                //See if we have a message to send
                vector<char> &toSend = messageQueue[sockfd];
                if (toSend.size() != 0) {
                    size_t sentLength = send(sockfd, toSend.data(), toSend.size(), MSG_DONTWAIT);
                    if (sentLength > 0) {
                        //Didn't get an error
                        toSend.erase(toSend.begin(), toSend.begin()+sentLength);
                    }
                }
            }
		}
	}
}

int PiServer::connectToClient(int serverfd, fd_set *masterfds, int *maxfd) {
	struct sockaddr_storage remoteaddr; //New client address

	//Accept connection
	socklen_t addrlen = sizeof remoteaddr;
	int clientfd = accept(serverfd, (struct sockaddr *)&remoteaddr, &addrlen);

	if (clientfd != -1) {
		//Successful connection, add to master set
        FD_SET(clientfd, masterfds);
		if (clientfd > *maxfd) {    // keep track of the max
			*maxfd = clientfd;
		}
        
        //Make sure we have an empty messageQueue for the new client
        messageQueue[clientfd] = vector<char>();
   
		//Print out where we got a connection from
		char remoteIP[INET6_ADDRSTRLEN];
		cout << "New connection from " << inet_ntop(remoteaddr.ss_family, getInternetAddress((struct sockaddr*)&remoteaddr), remoteIP, INET6_ADDRSTRLEN)
			<<" on socket " << to_string(clientfd) << endl;
	}else {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            cerr << "Error accepting socket that would block" << endl;
        }else {
            cerr << "Accepting new client failed with error number: " << to_string(errno) << endl;
        }
    }
	return clientfd;
}

void * PiServer::getInternetAddress(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
    
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void PiServer::registerDefaultParsers() {
    PiParser::getInstance().registerParserForID(new PingParser(), kPingParserID, kPingParserID);
}