#include "ClientManager.h"
#include "PiParser.h"
#include "PiServer.h"
#include <netinet/in.h>
#include <iostream>
using namespace std;
#pragma mark - Constructors
ClientManager::ClientManager(PiParser *defaultParser, PiServer *piServer): _defaultParser(defaultParser), _piServer(piServer) {

}
#pragma mark - Desctuctors

#pragma mark - Instance Methods

void ClientManager::newClientConnection(int portNumber) {
	Client newStatus;
	newStatus.messageStatus = MessageStatusNone;
	clientStatus[portNumber] = newStatus;
}

PiMessage ClientManager::receivedMessageOnPort(const char *message, int messageLength, int portNumber) {
	if (!clientStatus.count(portNumber)) {
		newClientConnection(portNumber);
	}
	Client status = clientStatus[portNumber];

	if (status.messageStatus == MessageStatusNone) {
		//Brand new message. Get the header length and header
		uint16_t headerLength;
        int prefixBytes = sizeof(headerLength);
		memcpy(&headerLength, message, prefixBytes);
		headerLength = ntohs(headerLength);

		PiHeader header;
		header.ParseFromArray(message+prefixBytes, headerLength);
        
        cout << "Message size: " << header.messagelength() << endl;
        //Initialize from a char array
        const char *messageStart = message+prefixBytes+headerLength;
        const char *messageEnd = messageStart+header.messagelength();
        
		status.message = std::vector<char>(messageStart, messageEnd);
		status.messageStatus = MessageStatusPartial;
		status.header = header;
	}else {
		//Already part of an old message
		status.message.insert(status.message.end(), message, message+messageLength);
	}

	PiMessage response;
    
    cout << "Message on port: " << to_string(portNumber) << " total size: " << to_string(status.header.messagelength()) << " received size: " << status.message.size() << endl;

	//Check if message is complete
	if (status.header.messagelength() - status.message.size() <= 0) {
		//Parse it and clear
		status.messageStatus = MessageStatusNone;
        
        response = _defaultParser->parseData(status.header, status.message, portNumber);
	}

	return response;
}

void ClientManager::clientDisconnected(int portNumber) {
    Client c = clientStatus[portNumber];
    
    //Remove from each group
    for (std::string &groupID : c.groups)
        removeClientFromGroup(portNumber, groupID);
    
	clientStatus.erase(portNumber);
}

#pragma mark - Client Group Methods

void ClientManager::addClientToGroup(int clientID, const std::string &groupID) {
    groups[groupID].insert(clientID);
}

void ClientManager::addClientToGroup(int clientID, uint32_t clientFlags, const std::string &groupID) {
    Client c = clientStatus[clientID];
    c.clientFlags = clientFlags;
    
    addClientToGroup(clientID, groupID);
}

void ClientManager::removeClientFromGroup(int clientID, const std::string &groupID) {
    std::set<int> &group = groups[groupID];
    
    group.erase(clientID);
}

int ClientManager::sizeOfGroup(const std::string &groupID) {
    return groups[groupID].size();
}

void ClientManager::sendMessageToGroup(PiMessage &message, const std::string &groupID) {
    std::set<int> &group = groups[groupID];
    
    for (int clientID : group) {
        _piServer->sendMessageToClientWithID(clientID, message);
    }
}

void ClientManager::sendMessageToGroup(PiMessage &message, const std::string &groupID, uint32_t clientFlags) {
    std::set<int> &group = groups[groupID];
    
    for (int clientID : group) {
        Client c = clientStatus[clientID];
        
        if ((c.clientFlags & clientFlags) != 0) {
            _piServer->sendMessageToClientWithID(clientID, message);
        }
    }
}