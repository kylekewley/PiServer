#ifndef Custom_Buffer_Parser_h
#define Custom_Buffer_Parser_h

#include "CustomParser.h"
#include "Constants.h"


template <typename T> class CustomBufferParser : public CustomParser {
protected:
	mutable T inputMessage;
public:
    ~CustomBufferParser() {};
	CustomBufferParser() {
        static_assert(std::is_base_of<ProtocolBuffer, T>::value, "T not derived from google::protocol::MessageLite");
    };
	PiMessage parse(std::vector<char> data, int clientID) const;
    
    /**
     *Parse the MessageLite object and return another MessageLite 
     *object. The returned object will be deleted by the calling
     *function.
     *@param    data    The data to parse
     *@return   A new ProtocolBuffer object to be sent back to the client
     *
     *@discussion   A subclass should return null if the client does not need a response.
     */
	virtual ProtocolBuffer *parseBuffer(const T *data, int clientID) const = 0;
	
};

#endif