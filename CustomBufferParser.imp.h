//
//  CustomBufferParser.imp.h
//  PiServer
//
//  Created by Kyle Kewley on 5/16/14.
//  Copyright (c) 2014 Kyle Kewley. All rights reserved.
//

#ifndef PiServer_CustomBufferParser_imp_h
#define PiServer_CustomBufferParser_imp_h
#include "CustomBufferParser.h"

using namespace std;

#pragma mark - Parsing
template <typename T>
std::vector<char> CustomBufferParser<T>::parse(std::vector<char> data) {
	inputMessage->ParseFromArray(data.data(), data.size());
	ProtocolBuffer *output = parseBuffer(inputMessage);
    
    //Create a vector the size of output
    std::vector<char> vector = std::vector<char>(output->ByteSize());
	output->SerializeToArray(vector.data(), vector.size());
    
    delete output;
    
	return vector;
}
#endif
