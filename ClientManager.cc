#include "ClientManager.h"
#include "PiParser.h"
#include <netinet/in.h>
#include <iostream>
using namespace std;
#pragma mark - Constructors
ClientManager::ClientManager(PiParser *defaultParser): _defaultParser(defaultParser) {

}
#pragma mark - Desctuctors

#pragma mark - Instance Methods

void ClientManager::newClientConnection(int portNumber) {
	ClientStatus newStatus;
	newStatus.messageStatus = MessageStatusNone;
	clientStatus[portNumber] = newStatus;
}

PiMessage ClientManager::receivedMessageOnPort(const char *message, int messageLength, int portNumber) {
	if (!clientStatus.count(portNumber)) {
		newClientConnection(portNumber);
	}
	ClientStatus status = clientStatus[portNumber];

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
        
        response = _defaultParser->parseData(status.header, status.message);
	}

	return response;
}

void ClientManager::clientDisconnected(int portNumber) {
	clientStatus.erase(portNumber);
}