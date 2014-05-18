#include "ClientManager.h"
#include "PiParser.h"
#include <netinet/in.h>
#include <iostream>
using namespace std;
#pragma mark - Constructors
ClientManager::ClientManager() {

}
#pragma mark - Desctuctors

#pragma mark - Instance Methods

void ClientManager::newClientConnection(int portNumber) {
	ClientStatus newStatus;
	newStatus.messageStatus = MessageStatusNone;
	clientStatus[portNumber] = newStatus;
}

std::vector<char> ClientManager::receivedMessageOnPort(const char *message, int messageLength, int portNumber) {
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

	std::vector<char> response = std::vector<char>();
    
    cout << "Message on port: " << to_string(portNumber) << " total size: " << to_string(status.header.messagelength()) << " received size: " << status.message.size() << endl;

	//Check if message is complete
	if (status.header.messagelength() - status.message.size() <= 0) {
		//Parse it and clear
		status.messageStatus = MessageStatusNone;
        std::vector<char> parseResponse = PiParser::getInstance().parseData(status.header, status.message);
        status.header.set_messagelength(static_cast<uint32_t>(parseResponse.size()));
        
        response = generateMessage(status.header, parseResponse);
        
	}

	return response;
}

std::vector<char> ClientManager::generateMessage(PiHeader &header, std::vector<char> &reply) {
    int16_t headerLength = header.ByteSize();
    int prefixBytes = sizeof(headerLength); //Size of the prefix
    
    std::vector<char> messageVector;
    messageVector.resize(prefixBytes+headerLength+reply.size()); //Allocate storage
    
    //Copy the header length prefix
    char *data = &messageVector[0];
    int16_t networkHeaderLength = htons(headerLength); //Convert for sending on the network
    memcpy(data, &networkHeaderLength, prefixBytes);
    
    //Copy the header
    header.SerializeToArray(data+prefixBytes, headerLength);
    
    //Copy the data
    messageVector.insert(messageVector.begin()+prefixBytes+headerLength, reply.begin(), reply.end());
    
    return messageVector;
}
void ClientManager::clientDisconnected(int portNumber) {
	clientStatus.erase(portNumber);
}