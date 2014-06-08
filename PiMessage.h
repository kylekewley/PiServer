//
//  PiMessage.h
//  PiServer
//
//  Created by Kyle Kewley on 6/7/14.
//  Copyright (c) 2014 Kyle Kewley. All rights reserved.
//

#ifndef __PiServer__PiMessage__
#define __PiServer__PiMessage__

#include "Constants.h"
#include "PiHeader.pb.h"

#include <vector>

using namespace std;

class PiMessageCallback {
public:
    virtual void messageReceivedByServer(PiHeader &header) = 0;
    virtual void serverErrorParsingMessage(PiHeader &header, kErrorCode errorNumber) = 0;
};

class PiMessage {
public:
    
    /**
     *@param    parserID    The PiServer parserID setup to parse the data
     *@param    message     binary data to send to the server
     */
    PiMessage(unsigned long parserID, vector<char> &message);
    
    /**
     *@param    parserID    The PiServer parserID setup to parse the Protocol Buffer object
     *@param    pBuffer     The generated Protocol Buffer object to send to the server
     */
    PiMessage(unsigned long parserID, ProtocolBuffer &pBuffer);
    
    /**
     *@param    header  The PiHeader to use for the message
     *@param    message The binary data to send to the server
     */
    PiMessage(PiHeader &header, vector<char> &message);
    
    
    /**
     *Set the flag to true
     *@param    flag    The flag to set true
     */
    void setFlagTrue(kPiHeaderFlag flag);
    
    /**
     *Set the flag to false
     *@param    flag    The flag to set false
     */
    void setFlagFalse(kPiHeaderFlag flag);
    
    /**
     *Get the current value of the flag
     *@param    flag    The flag to get the value of
     */
    bool getFlagValue(kPiHeaderFlag flag);
    
    /**
     *Writes the message data to the given buffer up to length bytes
     *
     *@discussion   If the buffer is too small to hold the full message,
     *additional calls to this method will push remaining data into the buffer
     *
     *@param    buffer  A buffer that is at least size length
     *@param    length  The maximum number of bytes to write to the buffer
     *
     *@return   The number of bytes written to the buffer
     */
    long writeToBuffer(void *buffer, long length);
    
    /**
     *
     *@return   The number of bytes that have NOT yet been written to a buffer
     */
    long bytesRemaining();
    
    /**
     *The next write call will begin writing from the beginning of the message
     *
     */
    void resetWrite();
    
    /**
     *The size of the entire message in bytes
     */
    long serializedSize();
    
    
    PiMessageCallback *messageDelegate;
    
private:
    /**
     *@abstract Create a new PiHeader object with the given values
     *
     */
    PiHeader generateHeader(unsigned long parserID, unsigned long flags, unsigned long messageID, unsigned long messageLength);
    
    /**
     *Calls -headerBuilderWithParserID:flags:messageID:messageLength: with flags set to zero and a uniqueMessageID value
     *
     */
    PiHeader generateHeader(unsigned long parserID, unsigned long messageLength);
        
    /**
     *Serialized the Protocol buffer object to the vector
     *
     *@param    message     The message to write to a vector
     *
     *@return   A vector containing the serialized data from the message
     */
    vector<char> serializeMessageToVector(ProtocolBuffer &message);
    
    PiHeader messageHeader;
    
    vector<char> headerData;
    vector<char> messageData;
    
    long totalBytesSent;
};

#endif /* defined(__PiServer__PiMessage__) */
