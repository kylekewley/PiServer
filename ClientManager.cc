#include "ClientManager.h"
#include "PiParser.h"

void ClientManager::newClientConnection(int portNumber) {
	ClientStatus newStatus;
	newStatus.messageStatus = MessageStatusNone;
	clientStatus[portNumber] = newStatus;
}

void ClientManager::receivedMessageOnPort(const char *message, PiHeader &header, int messageLength, int portNumber) {
	if (!clientStatus.count(portNumber)) {
		newClientConnection(portNumber);
	}
	ClientStatus status = clientStatus[portNumber];

	if (status.messageStatus == MessageStatusNone) {
		//Brand new message
		status.message = std::string(message, messageLength);
		status.messageStatus = MessageStatusWaiting;
		status.receivedLength = messageLength;
		status.remainingLength = header.messagelength() - messageLength;
		status.header = header;
	}else {
		//Already part of an old message
		status.message.append(message, messageLength);
		status.receivedLength += messageLength;
		status.remainingLength -= messageLength;
	}

	//Check if message is complete
	if (status.remainingLength <= 0) {
		//Parse it and clear
		status.messageStatus = MessageStatusNone;
		std::string response = PiParser::getInstance().parseData(status.message, status.receivedLength);
		//TODO: Send the response
	}
}

void ClientManager::clientDisconnected(int portNumber) {
	//TODO: Memory management?
	clientStatus.erase(portNumber);
}