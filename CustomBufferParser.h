#ifndef Custom_Buffer_Parser_h
#define Custom_Buffer_Parser_h

#include "Constants.h"
#include "CustomParser.h"


template <typename T> class CustomBufferParser : public CustomParser {
protected:
	T *inputMessage;
public:
    ~CustomBufferParser() {delete inputMessage;};
	CustomBufferParser(): inputMessage(new T()) {
        static_assert(std::is_base_of<ProtocolBuffer, T>::value, "T not derived from google::protocol::MessageLite");
    };
	PiMessage parse(std::vector<char> data, unsigned long messageID);
    
    /**
     *Parse the MessageLite object and return another MessageLite 
     *object. The returned object will be deleted by the calling
     *function.
     *@param    data    The data to parse
     *@return   A new ProtocolBuffer object to be sent back to the client
     */
	virtual ProtocolBuffer *parseBuffer(const T *data) = 0;
	
};

#endif