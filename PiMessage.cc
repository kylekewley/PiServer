//
//  PiMessage.cc
//  PiServer
//
//  Created by Kyle Kewley on 6/7/14.
//  Copyright (c) 2014 Kyle Kewley. All rights reserved.
//

#include "PiMessage.h"

//Used for generating unique message IDs
//Clients start at 0 and count up, the server starts at ULONG_MAX and counts down
static unsigned long uniqueMessageID = ULONG_MAX;

#pragma mark - Constructors

PiMessage::PiMessage(unsigned long parserID, vector<char> &message) {
    messageHeader = generateHeader(parserID, message.size());
    messageData = message;
}

PiMessage::PiMessage(unsigned long parserID, ProtocolBuffer &pBuffer) {
    messageHeader = generateHeader(parserID, pBuffer.ByteSize());
    
    messageData = serializeMessageToVector(pBuffer);

}

PiMessage::PiMessage(PiHeader &header, vector<char> &message): messageHeader(header), messageData(message) {}

PiMessage::PiMessage(unsigned long parserID) {
    messageHeader = generateHeader(parserID, 0);
}

PiMessage::PiMessage(unsigned long parserID, unsigned long messageID) {
    messageHeader = generateHeader(parserID, kHeaderConfirmation, messageID, 0);
}

#pragma mark - Public Methods
#pragma mark Setting flag values

void PiMessage::setFlagTrue(kPiHeaderFlag flag) {
    if (totalBytesSent != 0) return;
    
    messageHeader.set_flags(messageHeader.flags() | flag);
    
}

void PiMessage::setFlagFalse(kPiHeaderFlag flag) {
    if (totalBytesSent != 0) return;
    
    messageHeader.set_flags(messageHeader.flags() & ~flag);
}

bool PiMessage::getFlagValue(kPiHeaderFlag flag) {
    return ((messageHeader.flags() & flag) != 0);
}

#pragma mark Writing to the buffer
long PiMessage::writeToBuffer(void *buffer, long length) {
    if (headerData.size() == 0) {
        headerData = serializeMessageToVector(messageHeader);
    }
    
    long spaceRemaining = length;
    
    if (totalBytesSent < headerData.size()) {
        //Still need to copy the header
        long copyLength = spaceRemaining;
        long headerRemaining = headerData.size() - totalBytesSent;
        
        if (spaceRemaining >= headerRemaining)
            copyLength = headerRemaining;
        
        //Start copying at the proper offset
        memcpy(buffer, headerData.data(), copyLength);
        
        totalBytesSent += copyLength;
        spaceRemaining -= copyLength;
    }
    
    if (totalBytesSent >= headerData.size()) {
        //Start sending the actual message
        long copyLength = spaceRemaining;
        long messageRemaining = messageData.size() + headerData.size() - totalBytesSent;
        
        if (spaceRemaining >= messageRemaining)
            copyLength = messageRemaining;
        
        long messageOffset = totalBytesSent - headerData.size();
        
        memcpy(static_cast<void *>(static_cast<char *>(buffer)+(spaceRemaining-length)), messageData.data()+messageOffset, copyLength);
        
        totalBytesSent += copyLength;
        spaceRemaining -= copyLength;
    }
    
    return length-spaceRemaining;
}

long PiMessage::bytesRemaining() {
    return serializedSize() - totalBytesSent;
}


void PiMessage::resetWrite() {
    totalBytesSent = 0;
    //Set headerData to an empty vector
    headerData = vector<char>(0);
}

long PiMessage::serializedSize() {
    return messageHeader.ByteSize() + messageData.size() + sizeof(prefix_t);
}


#pragma mark - Private Methods

PiHeader PiMessage::generateHeader(unsigned long parserID, unsigned long flags, unsigned long messageID, unsigned long messageLength) {
    PiHeader tmpHeader;
    
    tmpHeader.set_parserid(parserID);
    tmpHeader.set_flags(flags);
    tmpHeader.set_messageid(messageID);
    tmpHeader.set_messagelength(messageLength);
    
    return tmpHeader;
}

PiHeader PiMessage::generateHeader(unsigned long parserID, unsigned long messageLength) {
    return generateHeader(parserID, 0, --uniqueMessageID, messageLength);
}


vector<char> PiMessage::serializeMessageToVector(ProtocolBuffer &message) {
    vector<char> tmp = vector<char>(message.ByteSize());
	message.SerializeToArray(tmp.data(), static_cast<int>(tmp.size()));
    
    return tmp;
}