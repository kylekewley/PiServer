#include "ClientManager.h"
#include "PiParser.h"
#include <netinet/in.h>

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
		memcpy(&headerLength, message, sizeof(headerLength));
		headerLength = ntohs(headerLength);

		PiHeader header;
		header.ParseFromArray(message+2, headerLength);

        //Initialize from a char array
        const char *messageStart = message+2+headerLength;
        const char *messageEnd = messageStart+messageLength;
		status.message = std::vector<char>(messageStart, messageEnd);
		status.messageStatus = MessageStatusPartial;
		status.header = header;
	}else {
		//Already part of an old message
		status.message.insert(status.message.end(), message, message+messageLength);
	}

	std::vector<char> response = std::vector<char>();
	//Check if message is complete
	if (status.header.messagelength() - status.message.size() <= 0) {
		//Parse it and clear
		status.messageStatus = MessageStatusNone;
        response = PiParser::getInstance().parseData(status.header, status.message);
	}

	return response;
}

void ClientManager::clientDisconnected(int portNumber) {
	clientStatus.erase(portNumber);
}