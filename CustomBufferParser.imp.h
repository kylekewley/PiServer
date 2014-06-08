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

using namespace std;

#pragma mark - Parsing
template <typename T>
PiMessage CustomBufferParser<T>::parse(std::vector<char> data, unsigned long messageID) {
	inputMessage->ParseFromArray(data.data(), static_cast<int>(data.size()));
	ProtocolBuffer *outputBuffer = parseBuffer(inputMessage);
    
    PiMessage output = PiMessage(0, *outputBuffer);
    
    output.messageHeader.set_messageid(messageID);
    output.setFlagTrue(kHeaderConfirmation);
    
    return output;
}
#endif
