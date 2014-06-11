//
//  PiErrorMessage.h
//  PiServer
//
//  Created by Kyle Kewley on 6/8/14.
//  Copyright (c) 2014 Kyle Kewley. All rights reserved.
//

#ifndef __PiServer__PiErrorMessage__
#define __PiServer__PiErrorMessage__

#include <string>

#include "PiMessage.h"
#include "Constants.h"

#include "ParseError.pb.h"

using namespace std;

class PiErrorMessage : public PiMessage {
public:
    
    PiErrorMessage(kErrorCode error, const string &errorMessage);
    
    
    /**
     *This creates an error message with the default error message from the errorStrings map in Constants.h
     */
    PiErrorMessage(kErrorCode error);
    
private:
    ParseError parseError;
    
    ParseError generateParseErrorMessage(kErrorCode error, const string &errorMessage);
};


#endif /* defined(__PiServer__PiErrorMessage__) */
