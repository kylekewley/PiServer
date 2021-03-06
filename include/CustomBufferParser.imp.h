//
//  CustomBufferParser.imp.h
//  PiServer
//
//  Created by Kyle Kewley on 5/16/14.
//  Copyright (c) 2014 Kyle Kewley. All rights reserved.
//

#ifndef PiServer_CustomBufferParser_imp_h
#define PiServer_CustomBufferParser_imp_h
#include <iostream>

#include "CustomBufferParser.h"
#include "PiErrorMessage.h"
#include "Constants.h"

using namespace std;

#pragma mark - Parsing
template <typename T>
PiMessage CustomBufferParser<T>::parse(vector<char> data, int clientID) const{
	inputMessage.ParseFromArray(data.data(), static_cast<int>(data.size()));
	
    if (!inputMessage.IsInitialized()) {
        //Unable to parse the message
        return PiErrorMessage(kUnableToParseMessage);
    }
    
    //Call the subclass's implementation of parseBuffer
    ProtocolBuffer *outputBuffer = parseBuffer(&inputMessage, clientID);
    
    //Default to an empty PiMessage object that wont send data
    PiMessage tmpMessage;
    
    if (outputBuffer != NULL) {
        //Return a new PiMessage with a parserID of 0 and the returned outputBuffer
        tmpMessage = PiMessage(0, *outputBuffer);
        
        //Delete the dynamically allocated ProtocolBuffer
        delete outputBuffer;
    }

    return tmpMessage;

}
#endif
