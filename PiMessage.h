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


class PiMessage {
public:
    
    /**
     *Creates an empty PiMessage object that will not send any data
     */
    PiMessage();
    
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
     *Constructor for when we just want to send a reply header with no data
     *
     *@param    parserID    The PiClient parserID setup to parse the header response
     */
    PiMessage(unsigned long parserID);
    
    /**
     *Constructor for sending a PiMessage reply with a header and no data.
     *
     *@param    parserID    The PiClient parserID setup to parse the header response
     *@param    messageID   The ID of the message to send back to the client
     */
    PiMessage(unsigned long parserID, unsigned long messageID);
    
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
     *Moves the write pointer back a given number of bytes.
     *
     *@param    bytes   The number of bytes to move the writePointer backwards
     *
     *@discussion   If bytes > totalBytesSent, totalBytesSent will be set to zero.
     */
    void moveWritePointerBack(unsigned long bytes);
    
    /**
     *The next write call will begin writing from the beginning of the message
     *
     */
    void resetWrite();
    
    /**
     *The size of the entire message in bytes
     */
    long serializedSize();
    
    PiHeader messageHeader;
    
    bool isEmpty;

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
     *Create a new vector object with the PiHeader already written to it
     *
     *@param    header  The initialized header to write to the output stream
     *@return   A vector object ready for the message to be appended to
     */
    vector<char> serializedVectorFromHeader(PiHeader &header);
    
    /**
     *Serialized the Protocol buffer object to the vector
     *
     *@param    message     The message to write to a vector
     *
     *@return   A vector containing the serialized data from the message
     */
    vector<char> serializeMessageToVector(ProtocolBuffer &message);
    
    /**
     *Copy as much of the data as possible to the given buffer
     *
     *@param    data    The data to copy to the buffer
     *@param    buffer  The buffer where the data will be copied to
     *@param    dataLength  The length of the data array to copy
     *@param    bufferLength    The length of the buffer that we are allowed to copy to
     *
     *@return   The acutal number of bytes copied to the buffer
     */
    unsigned long copyDataToBuffer(const void *data, void *buffer, unsigned long dataLength, unsigned long bufferLength);
    
    vector<char> headerData;
    vector<char> messageData;
    
    long totalBytesSent;
};

#endif /* defined(__PiServer__PiMessage__) */
