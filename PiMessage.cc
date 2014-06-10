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

PiMessage::PiMessage(): isEmpty(true) {
}

PiMessage::PiMessage(uint32_t parserID, vector<char> &message): isEmpty(false), totalBytesSent(0) {
    messageHeader = generateHeader(parserID, message.size());
    messageData = message;
}

PiMessage::PiMessage(uint32_t parserID, ProtocolBuffer &pBuffer): isEmpty(false), totalBytesSent(0) {
    messageHeader = generateHeader(parserID, pBuffer.ByteSize());
    
    messageData = serializeMessageToVector(pBuffer);

}

PiMessage::PiMessage(PiHeader &header, vector<char> &message): isEmpty(false), messageHeader(header), messageData(message), totalBytesSent(0) {}

PiMessage::PiMessage(uint32_t parserID): isEmpty(false), totalBytesSent(0) {
    messageHeader = generateHeader(parserID, 0);
}

PiMessage::PiMessage(uint32_t parserID, uint32_t messageID): isEmpty(false), totalBytesSent(0) {
    messageHeader = generateHeader(parserID, 0, messageID, 0);
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
    if (isEmpty)
        return 0;
    
    if (headerData.size() == 0) {
        headerData = serializedVectorFromHeader(messageHeader);
    }
    
    long spaceRemaining = length;
    
    if (totalBytesSent < headerData.size()) {
        //Still need to copy the header
        long headerRemaining = headerData.size() - totalBytesSent;
        
        unsigned long copyLength = copyDataToBuffer(headerData.data()+totalBytesSent, buffer, headerRemaining, spaceRemaining);
        
        
        totalBytesSent += copyLength;
        spaceRemaining -= copyLength;
        //Move the buffer pointer so our next copy to it is at the correct position
        buffer = static_cast<char *>(buffer)+copyLength;
    }
    
    if (totalBytesSent >= headerData.size()) {
        //Start sending the actual message
        long messageRemaining = messageData.size() + headerData.size() - totalBytesSent;
        long messageOffset = totalBytesSent - headerData.size();

        unsigned long copyLength = copyDataToBuffer(messageData.data()+messageOffset, buffer, messageRemaining, spaceRemaining);
        
        
        totalBytesSent += copyLength;
        spaceRemaining -= copyLength;
        buffer = static_cast<char *>(buffer)+copyLength;
    }
    
    return length-spaceRemaining;
}

long PiMessage::bytesRemaining() {
    return serializedSize() - totalBytesSent;
}

void PiMessage::moveWritePointerBack(unsigned long bytes) {
    totalBytesSent -= bytes;
    if (totalBytesSent < 0)
        totalBytesSent = 0;
}

void PiMessage::resetWrite() {
    totalBytesSent = 0;
    //Set headerData to an empty vector
    headerData = vector<char>(0);
}

long PiMessage::serializedSize() {
    if (isEmpty)
        return 0;
    
    return messageHeader.ByteSize() + messageData.size() + sizeof(prefix_t);
}


#pragma mark - Private Methods

PiHeader PiMessage::generateHeader(uint32_t parserID, uint32_t flags, uint32_t messageID, uint32_t messageLength) {
    PiHeader tmpHeader;
    
    tmpHeader.set_parserid(parserID);
    tmpHeader.set_flags(flags);
    tmpHeader.set_messageid(messageID);
    tmpHeader.set_messagelength(messageLength);
    
    return tmpHeader;
}

PiHeader PiMessage::generateHeader(uint32_t parserID, uint32_t messageLength) {
    return generateHeader(parserID, 0, --uniqueMessageID, messageLength);
}

vector<char> PiMessage::serializedVectorFromHeader(PiHeader &header) {
    vector<char> headerVector = vector<char>(header.ByteSize()+sizeof(prefix_t));
    
    char *vectorPtr = headerVector.data();
    
    prefix_t headerLength = header.ByteSize();
    headerLength = hpton(headerLength);
    
    memcpy(vectorPtr, &headerLength, sizeof(headerLength));
    vectorPtr += sizeof(headerLength);
    
    header.SerializeToArray(vectorPtr, header.ByteSize());
    
    return headerVector;
}

vector<char> PiMessage::serializeMessageToVector(ProtocolBuffer &message) {
    vector<char> tmp = vector<char>(message.ByteSize());
	message.SerializeToArray(tmp.data(), static_cast<int>(tmp.size()));
    
    return tmp;
}

unsigned long PiMessage::copyDataToBuffer(const void *data, void *buffer, unsigned long dataLength, unsigned long bufferLength) {
    unsigned long maxCopy = dataLength;
    
    if (dataLength > bufferLength)
        maxCopy = bufferLength; //Prevent overflow
    
    memcpy(buffer, data, maxCopy);
    
    return maxCopy;
}