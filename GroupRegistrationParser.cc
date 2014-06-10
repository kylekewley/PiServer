//
//  GroupRegistrationParser.cc
//  PiServer
//
//  Created by Kyle Kewley on 6/9/14.
//  Copyright (c) 2014 Kyle Kewley. All rights reserved.
//

#include "GroupRegistrationParser.h"

#include "ClientManager.h"

#include "GroupRegistration.pb.h"

GroupRegistrationParser::GroupRegistrationParser(ClientManager &clientManager): _clientManager(clientManager) {
    
}
ProtocolBuffer *GroupRegistrationParser::parseBuffer(const GroupRegistration *data, int clientID) {
    //Register with the clientManager given in the constructor
    uint32_t flags = 0;
    if (data->has_flags())
        flags = data->flags();
    if (data->addtogroup())
        _clientManager.addClientToGroup(clientID, flags, data->groupid());
    else
        _clientManager.removeClientFromGroup(clientID, data->groupid());
    
    return NULL;
}