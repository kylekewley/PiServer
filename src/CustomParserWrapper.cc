//
//  CustomParserWrapper.cc
//  PiServer
//
//  Created by Kyle Kewley on 6/18/14.
//  Copyright (c) 2014 Kyle Kewley. All rights reserved.
//

#include "CustomParserWrapper.h"


CustomParserWrapper::CustomParserWrapper(Range r, CustomParser *p): range(r), parser(p->clone()) {

}

CustomParserWrapper::CustomParserWrapper(int parserID): range(Range(parserID, parserID)), parser(NULL) {
    
}

CustomParserWrapper::CustomParserWrapper(const CustomParserWrapper& customParserWrapper): range(customParserWrapper.range), parser(customParserWrapper.parser->clone()) {
    
}

CustomParserWrapper& CustomParserWrapper::operator=(const CustomParserWrapper& customParserWrapper) {
    range = customParserWrapper.range;
    parser = customParserWrapper.parser->clone();
    return *this;
}

CustomParserWrapper::~CustomParserWrapper() {
    delete parser;
}