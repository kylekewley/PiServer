//
//  CustomParserWrapper.cc
//  PiServer
//
//  Created by Kyle Kewley on 6/18/14.
//  Copyright (c) 2014 Kyle Kewley. All rights reserved.
//

#include "CustomParserWrapper.h"


CustomParserWrapper::CustomParserWrapper(Range r, std::shared_ptr<CustomParser> &p): range(r), parser(p) {

}

CustomParserWrapper::CustomParserWrapper(int parserID): range(Range(parserID, parserID)) {
    
}