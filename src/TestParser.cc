#include "TestParser.h"
#include "TestMessage.pb.h"
#include <iostream>


using namespace std;
//Pass in the type of protocol buffer to parse with
TestParser::TestParser() {

}


ProtocolBuffer *TestParser::parseBuffer(const TestMessage *data, int clientID) const {
	TestMessage *message = new TestMessage();
    string responseString = string("Response to: ");
    if (data->has_message()) {
        responseString += data->message();
    }else {
        responseString += "Empty Message";
    }
    message->set_message(responseString);
    
    cout << "Sending response " << responseString << endl;
    return message;
}

