#ifndef Custom_Parser_h
#define Custom_Parser_h


class CustomParser {
public:
	CustomParser() {};
	virtual std::vector<char> parse(std::vector<char> data) {return std::vector<char>();};
};

#endif