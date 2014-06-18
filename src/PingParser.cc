//
//  PingParser.cc
//  PiServer
//
//  Created by Kyle Kewley on 5/16/14.
//  Copyright (c) 2014 Kyle Kewley. All rights reserved.
//

#include "PingParser.h"
#include "Ping.pb.h"
#include <iostream>

PingParser::PingParser() {
    
}

PingParser::PingParser(const PingParser& pingParser) {
    //Nothing to copy
}

ProtocolBuffer *PingParser::parseBuffer(const Ping *data, int clientID) {
    Ping *message = new Ping(*data);
    return message;
}

PingParser* PingParser::clone() const{
    return new PingParser(*this);
}