#ifndef Constants_h
#define Constants_h 

#include <google/protobuf/message.h>

const int kPingParserID = 0;
const int kTestParserID = 1;


typedef ::google::protobuf::MessageLite ProtocolBuffer;
typedef std::pair<int, int> Range;

#endif
