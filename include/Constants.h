#ifndef Constants_h
#define Constants_h 

#include <google/protobuf/message.h>

//Used for generating unique message IDs
//Clients start at 0 and count up, the server starts at ULONG_MAX and counts down
static uint32_t kUniqueMessageID = UINT32_MAX;

inline uint32_t getUniqueMessageID() {
    return --kUniqueMessageID;
}

typedef enum {
    kEmptyParserID      = 0, //Don't register a parser for zero
    kPingParserID       = 1,
    kParseErrorID       = 2,
    kGroupParserID      = 3
}kDefaultParserID;


typedef ::google::protobuf::MessageLite ProtocolBuffer;
typedef std::pair<int, int> Range;


typedef enum {
    kErrorMessage   = 1UL << 0
}kPiHeaderFlag;

typedef enum {
    kNoParserFound,
    kInvalidData,
    kParserRuntimeException,
    kUnimplementedParser,
    kUnableToParseMessage
}kErrorCode;



inline std::string getErrorString(kErrorCode errorNo) {
    
    switch (errorNo) {
        case kNoParserFound:
            return std::string("There is no parser registered for the given parser ID.");
        case kInvalidData:
            return std::string("The data given to the parser was invalid.");
        case kParserRuntimeException:
            return std::string("The custom parser raised an exception and could not parse the data. This could result in undefined and unexpected behavior.");
        case kUnimplementedParser:
            return std::string("The custom parser subclass did not properly override the required methods.");
        case kUnableToParseMessage:
            return std::string("The server was unable to parse the protocol buffer object");
        default:
            return std::string("Unknown Error");
    }
}



typedef int16_t prefix_t;

///Network to host prefix
inline prefix_t ntohp(prefix_t n_prefix) {
    return (sizeof(prefix_t) == 2) ? ntohs(n_prefix) : ntohl(n_prefix);
}

///host prefix to network
inline prefix_t hpton(prefix_t h_prefix) {
    return (sizeof(prefix_t) == 2) ? htons(h_prefix) : htonl(h_prefix);
}

#endif
