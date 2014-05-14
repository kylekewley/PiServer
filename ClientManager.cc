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

std::string ClientManager::receivedMessageOnPort(const char *message, int messageLength, int portNumber) {
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

		status.message = std::string(message+2+headerLength, messageLength);
		status.messageStatus = MessageStatusPartial;
		status.header = header;
	}else {
		//Already part of an old message
		status.message.append(message, messageLength);
	}

	std::string response = NULL;
	//Check if message is complete
	if (status.header.messagelength() - status.message.length() <= 0) {
		//Parse it and clear
		status.messageStatus = MessageStatusNone;
		const char *cResponse;
		cResponse = PiParser::getInstance().parseData(status.header, status.message, status.message.length());
		response = std::string(cResponse);
	}

	return response;
}

void ClientManager::clientDisconnected(int portNumber) {
	clientStatus.erase(portNumber);
}