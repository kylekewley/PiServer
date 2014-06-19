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
#include <memory>
class PiServer;

typedef enum MessageStatus
{
	MessageStatusNone, 		//Waiting for a message
    MessageStatusPartialHeader,
	MessageStatusPartialMessage,	//Has a partial message
}MessageStatus;

typedef struct Client {
	MessageStatus messageStatus; //Either no message or a partial message
    std::vector<char> message;		//Copy of the current message char array buffer
	PiHeader header;
    prefix_t headerLength;
    
    uint32_t clientFlags;
    std::vector<string> groups;
}Client;

class ClientManager {
public:
    
    /**
     *Initialize the client manager with a PiParser
     *
     *@param    defaultParser   A weak pointer to the PiServer parser that will be used to generate responses
     */
	ClientManager(PiParser *defaultParser, PiServer *piServer);

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
    PiMessage receivedMessageOnPort(const char *message, size_t messageLength, unsigned long *lengthUsed, int portNumber);

	/**
	*destroys the ClientStatus object associated with the port
	*/
	void clientDisconnected(int portNumber);

    
    /**
     *Adds the client to the group. Creates a new group if the groupID doesn't exist.
     *
     *@param    clientID    The ID of the client to register
     *@param    groupID     The name of the group where the client should be added to
     *
     *@discussion       The clientFlags for the client will default to zero.
     */
    void addClientToGroup(int clientID, const std::string &groupID);
    
    /**
     *Adds the client to the group. Creates a new group if the groupID doesn't exist.
     *
     *@param    clientID    The ID of the client to register
     *@param    groupID     The name of the group where the client should be added to
     *@param    clientFlags The flags to be set for the client
     */
    void addClientToGroup(int clientID, uint32_t clientFlags, const std::string &groupID);
    
    /**
     *Removes the client to the group.
     *
     *@param    clientID    The ID of the client to register
     *@param    groupID     The name of the group where the client should be removed from
     */
    void removeClientFromGroup(int clientID, const std::string &groupID);
    
    /**
     *@param    groupID     The group to get the size of
     *
     *@return   The number of members belonging to the group.
     */
    size_t sizeOfGroup(const std::string &groupID);
    
    /**
     *Sends a message to all members of the group with the given groupID
     *
     *@param    message     The message to send to members of the group
     *@param    groupID     The groupID where the message should be sent to
     */
    void sendMessageToGroup(PiMessage &message, const std::string &groupID);
    
    /**
     *Sends a message to specific members of the given group.
     *
     *@param    message     The message to send to members of the group
     *@param    groupID     The groupID where the message should be sent to
     *@param    clientFlags The flags that the client must match for the message to be sent
     *
     *@discussion   Each client is registered with an unsigned long flags variable which defaults
            to zero. In order for the message to be sent to a client, the bitwise function
            ((client.flags & clientFlags) != 0) must return true.
     */
    void sendMessageToGroup(PiMessage &message, const std::string &groupID, uint32_t clientFlags);
    
    /**
     *Holds a weak reference to the server's default parser
     */
    PiParser *_defaultParser;
    
    /**
     *Holds a weak reference back to the server that created us
     */
    PiServer *_piServer;

private:
    
    /**
     *Associates each clientID with a client struct
     */
	std::map<int, Client> clientStatus;

    /**
     *The key is a group name
     *The value is a list of socket file descriptors that belong to the group
     */
    std::map<std::string, std::set<int>> groups;
    /**
     *Create a char vector containing the header prefix + serialized header + reply
     */
    std::vector<char> generateMessage(PiHeader &header, std::vector<char> &reply);
    
    bool parseHeaderLengthWithPartial(const char *data, unsigned long dataSize, vector<char> &storedData, unsigned long *oBytesUsed, prefix_t *oHeaderLength);
    
    bool parseHeaderWithPartial(const char *data, unsigned long dataSize, vector<char> &storedData, prefix_t headerLength, unsigned long *oBytesUsed, PiHeader *oHeader);
    
    void copyMessageData(const char *newData, unsigned long dataSize, vector<char> &storedData, unsigned long messageLength, unsigned long *oBytesUsed);
    
    unsigned long copyUpToLength(unsigned long maxLength, const char *data, unsigned long dataSize, vector<char> &storedData);
    
};

#endif
