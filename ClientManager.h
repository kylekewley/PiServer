///Connections are tracked by ports. Therefore, 
///ClientManager will use a map object with int keys
///to identify ports. A helper typedef struct ClientStatus
///will be used as the value and will track PiHeader,
///how many bytes have been transfered, and how many bytes
///remain. If the PiHeader and CustomParser allow partial
///data, the ClientStatus will not store a byte array of data.
///If either class does NOT allow partial data, ClientStatus
///will store the data until the message is complete.

///PiServer calls ClientManager. If message is complete, or
///partial messages are allowed, ClientManager calls on PiParser
///to parse the data.

#ifndef Client_Manager_h
#define Client_Manager_h

#include <map>
#include <string>
#include "PiHeader.pb.h"
typedef enum MessageStatus
{
	MessageStatusNone, 		//Waiting for a message
	MessageStatusPartial,	//Has a partial message
}MessageStatus;

typedef struct ClientStatus {
	MessageStatus messageStatus; //Either no message or a partial message
	std::string message;		//Copy of the current message char array buffer
	PiHeader header;
}ClientStatus;

class ClientManager {
public:
	ClientManager();

	/**
	*Register a new client to track
	*/
	void newClientConnection(int portNumber);

	/**
	*The PiServer calls this method whenever a message is received.
	*The ClientManager handles the message by storing it if it's incomplete,
	*or handing the complete message off to the PiParser. The PiParser returns
	*a response that the ClientManager sends back to the PiServer.
	*/
	std::string receivedMessageOnPort(const char *message, int messageLength, int portNumber);

	/**
	*destroys the ClientStatus object associated with the port
	*/
	void clientDisconnected(int portNumber);

private:
	std::map<int,ClientStatus> clientStatus;

};

#endif