//
//  GroupRegistrationParser.h
//  PiServer
//
//  Created by Kyle Kewley on 6/9/14.
//  Copyright (c) 2014 Kyle Kewley. All rights reserved.
//

#ifndef __PiServer__GroupRegistrationParser__
#define __PiServer__GroupRegistrationParser__

#include "CustomBufferParser.imp.h"

class GroupRegistration;
class ClientManager;

class GroupRegistrationParser : public CustomBufferParser<GroupRegistration> {
public:
    GroupRegistrationParser(ClientManager &clientManager);
    
    GroupRegistrationParser(const GroupRegistrationParser& groupRegistrationParser);
    
	ProtocolBuffer *parseBuffer(const GroupRegistration *data, int clientID);
    
    GroupRegistrationParser* clone() const;
private:
    ClientManager &_clientManager;
};

#endif /* defined(__PiServer__GroupRegistrationParser__) */
