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
#include "Constants.h"

using namespace std;

#pragma mark - Parsing
template <typename T>
PiMessage CustomBufferParser<T>::parse(std::vector<char> data) {
	inputMessage->ParseFromArray(data.data(), static_cast<int>(data.size()));
	
    //Call the subclass's implementation of parseBuffer
    ProtocolBuffer *outputBuffer = parseBuffer(inputMessage);
    
    //Return a new PiMessage with a parserID of 0 and the returned outputBuffer
    PiMessage tmpMessage = PiMessage(0, *outputBuffer);
    
    //Delete the dynamically allocated ProtocolBuffer
    delete outputBuffer;

    return tmpMessage;

}
#endif
