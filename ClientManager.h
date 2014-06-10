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
#include "PiMessage.h"
#include "PiParser.h"

typedef enum MessageStatus
{
	MessageStatusNone, 		//Waiting for a message
	MessageStatusPartial,	//Has a partial message
}MessageStatus;

typedef struct ClientStatus {
	MessageStatus messageStatus; //Either no message or a partial message
    std::vector<char> message;		//Copy of the current message char array buffer
	PiHeader header;
}ClientStatus;

class ClientManager {
public:
    
    /**
     *Initialize the client manager with a PiParser
     *
     *@param    defaultParser   A weak pointer to the PiServer parser that will be used to generate responses
     */
	ClientManager(PiParser *defaultParser);

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
    PiMessage receivedMessageOnPort(const char *message, int messageLength, int portNumber);

	/**
	*destroys the ClientStatus object associated with the port
	*/
	void clientDisconnected(int portNumber);

    /**
     *Holds a weak reference to the server's default parser
     */
    PiParser *_defaultParser;
    
private:
	std::map<int,ClientStatus> clientStatus;

    /**
     *The key is a group name
     *The value is a list of socket file descriptors that belong to the group
     */
    std::map<std::string, std::vector<int>> groups;
    /**
     *Create a char vector containing the header prefix + serialized header + reply
     */
    std::vector<char> generateMessage(PiHeader &header, std::vector<char> &reply);
};

#endif