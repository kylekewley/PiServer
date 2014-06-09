//
//  PiErrorMessage.cc
//  PiServer
//
//  Created by Kyle Kewley on 6/8/14.
//  Copyright (c) 2014 Kyle Kewley. All rights reserved.
//
#include "Constants.h"

#include "PiErrorMessage.h"
#include "ParseError.pb.h"

#pragma mark - Constructors

PiErrorMessage::PiErrorMessage(kErrorCode error, const string &errorMessage): parseError(generateParseErrorMessage(error, errorMessage)), PiMessage(kParseErrorID, parseError) {
    setFlagTrue(kErrorMessage);
}

PiErrorMessage::PiErrorMessage(kErrorCode error): parseError(generateParseErrorMessage(error, getErrorString(error))), PiMessage(kParseErrorID, parseError) {
}

#pragma mark - Private helper methods

ParseError PiErrorMessage::generateParseErrorMessage(kErrorCode error, const string &errorMessage) {
    ParseError errorResponse;
    
    errorResponse.set_errormessage(errorMessage);
    errorResponse.set_errornumber(error);
    
    return errorResponse;
}
