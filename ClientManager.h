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

typedef enum MessageStatus
{
	MessageStatusNone, 		//Waiting for a message
	MessageStatusWaiting,	//Has a partial message
}MessageStatus;

typedef struct ClientStatus {
	MessageStatus messageStatus;
	std::string message;
	int receivedLength;
	int totalLength;
	bool allowsPartial;
}ClientStatus;

class ClientManager {
public:
	ClientManager();
private:
	std::map<int,ClientStatus> clientStatuses;

};

#endif