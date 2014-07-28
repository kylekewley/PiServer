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

void printMessage(const char *message, int messageLength) {
    cout << "Received Message: ";
    for (int i = 0; i < messageLength; i++) {
        cout << hex << ((message[i] & 0xFFFF0000)>>4) << hex << (message[i] & 0x0000FFFF);
    }
    
    cout << endl;
}
PiMessage ClientManager::receivedMessageOnPort(const char *message, size_t messageLength, unsigned long *lengthUsed, int portNumber) {
	if (!clientStatus.count(portNumber)) {
		newClientConnection(portNumber);
	}
    
	Client &status = clientStatus[portNumber];
    

    *lengthUsed = 0;

    if (status.messageStatus == MessageStatusNone) {
        //Brand new message. Get the header length and header
        bool done = parseHeaderLengthWithPartial(message+*lengthUsed, messageLength-*lengthUsed, status.message, lengthUsed, &status.headerLength);
        
        if (done) {
            status.messageStatus = MessageStatusPartialHeader;
            status.message = vector<char>();
        }
    }
    
    if (status.messageStatus == MessageStatusPartialHeader) {
        unsigned long tmpUsed;
        
        bool done = parseHeaderWithPartial(message+*lengthUsed, messageLength-*lengthUsed, status.message, status.headerLength, &tmpUsed, &status.header);
        *lengthUsed += tmpUsed;
        
        if (done) {
            status.messageStatus = MessageStatusPartialMessage;
            status.message = vector<char>();
            
        }
    }
    
    if (status.messageStatus == MessageStatusPartialMessage) {
        unsigned long tmpUsed;
        
        copyMessageData(message+*lengthUsed, messageLength-*lengthUsed, status.message, status.header.messagelength(), &tmpUsed);
        *lengthUsed += tmpUsed;
        
        if (status.header.messagelength() == status.message.size()) {
            PiMessage response;
            
            response = _defaultParser->parseData(status.header, status.message, portNumber);

            //Parse it and clear
            status.messageStatus = MessageStatusNone;
            status.message = vector<char>();

            
            return response;

        }
    }
    
    
    return PiMessage();
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
    cout << "Adding client to group: " << groupID << endl;
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

size_t ClientManager::sizeOfGroup(const std::string &groupID) {
    return groups[groupID].size();
}

void ClientManager::sendMessageToGroup(PiMessage &message, const std::string &groupID) {
    std::set<int> &group = groups[groupID];
    std::cout << "Sending to group with count: " << to_string(group.size()) << std::endl;
    for (int clientID : group) {
		std::cout << "Sending to client with ID " << to_string(clientID) << std::endl;
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

bool ClientManager::parseHeaderLengthWithPartial(const char *data, unsigned long dataSize, vector<char> &storedData, unsigned long *oBytesUsed, prefix_t *oHeaderLength) {
    //Get bytes needed = prefix_t size - size we already have
    unsigned long bytesNeeded = sizeof(prefix_t) - storedData.size();
    
    unsigned long bytesCopied = copyUpToLength(bytesNeeded, data, dataSize, storedData);
    
    *oBytesUsed = bytesCopied;
    if (bytesCopied == bytesNeeded) {
        //Got it all
        prefix_t headerLength;
        memcpy(&headerLength, storedData.data(), storedData.size());
        headerLength = ntohp(headerLength);
        *oHeaderLength = headerLength;
        
        return true;
    }
    
    //Didn't get it all
    return false;
    
}

bool ClientManager::parseHeaderWithPartial(const char *data, unsigned long dataSize, vector<char> &storedData, prefix_t headerLength, unsigned long *oBytesUsed, PiHeader *oHeader) {
    unsigned long bytesNeeded = headerLength - storedData.size();
    
    unsigned long bytesCopied = copyUpToLength(bytesNeeded, data, dataSize, storedData);
    
    *oBytesUsed = bytesCopied;
    
    if (bytesCopied == bytesNeeded) {
        //Got it all
        oHeader->ParseFromArray(storedData.data(), static_cast<int>(storedData.size()));
        
        return true;
    }
    //Didn't get it all
    return false;
}

void ClientManager::copyMessageData(const char *newData, unsigned long dataSize, vector<char> &storedData, unsigned long messageLength, unsigned long *oBytesUsed) {
    unsigned long bytesNeeded = messageLength - storedData.size();
    
    unsigned long bytesCopied = copyUpToLength(bytesNeeded, newData, dataSize, storedData);
    *oBytesUsed = bytesCopied;
}

unsigned long ClientManager::copyUpToLength(unsigned long maxLength, const char *data, unsigned long dataSize, vector<char> &storedData) {
    unsigned long initialSize = storedData.size();
    
    if (dataSize < maxLength) {
        //Copy it all
        storedData.insert(storedData.end(), data, data+dataSize);
        
    }else {
        //Get the pointer so we can copy a set length
        storedData.insert(storedData.end(), data, data+maxLength);
    }
    
    return storedData.size() - initialSize;
}

