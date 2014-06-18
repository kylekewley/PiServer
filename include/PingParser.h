//
//  PingParser.h
//  PiServer
//
//  Created by Kyle Kewley on 5/16/14.
//  Copyright (c) 2014 Kyle Kewley. All rights reserved.
//

#ifndef __PiServer__PingParser__
#define __PiServer__PingParser__

#include "CustomBufferParser.imp.h"
#include "Ping.pb.h"
#include <iostream>
class Ping;

class PingParser : public CustomBufferParser<Ping> {
public:
    PingParser();

	ProtocolBuffer *parseBuffer(const Ping *data, int clientID) const;
    
};


#endif /* defined(__PiServer__PingParser__) */
