#ifndef Constants_h
#define Constants_h 

#include <google/protobuf/message.h>

const int kPingParserID = 0;
const int kTestParserID = 1;


typedef ::google::protobuf::MessageLite ProtocolBuffer;
typedef std::pair<int, int> Range;


typedef enum {
    kHeaderConfirmation     = 1 << 0
}kPiHeaderFlag;

typedef enum {
    kServerNoParserFound,
    kClientNoParserFound,
    kServerErrorParsingData,
    kClientErrorParsingData
}kErrorCode;


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
