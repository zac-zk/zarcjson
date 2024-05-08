#include "zarcjson.h"
#include "assert.h"

namespace zarcjson {

Parser::ParserPtr Parser::parser_ = nullptr;

Parser::Parser() {}
Parser::~Parser() {}
Parser::ParserPtr Parser::get_instance() {
	if(parser_ == nullptr){
		parser_ = Parser::ParserPtr(new Parser());
	}
	return parser_;
}

Type Parser::get_type(const Value& v) {
	assert(&v != nullptr);
	return v.type;
}

Result Parser::Parse(Value& v, const char* json) {
	Context c;
	assert(&v != nullptr);
	c.json = json;
	v.type = kNull;
	Result ret;
	Parser::ParseWhitespace(c);
	if((ret = Parser::ParseValue(c, v)) == kParseOk) {
		Parser::ParseWhitespace(c);
		if(*c.json != '\0') 
			ret = kParseRootNotSigular;
	}
	return ret;
}

Result Parser::ParseValue(Context& c, Value& v) {
	switch (*c.json) {
		case 'n': return ParseNull(c, v);
		case 't': return ParseTrue(c, v);
		case 'f': return ParseFalse(c, v);
		case '\0': return kParseExpectValue;
		default: return kParseInvalidValue;
	}
}

inline void Expect(Context& c, char ch) {
	assert(*c.json == ch);
	c.json++;
}

void Parser::ParseWhitespace(Context& c) {
	const char* p = c.json;
	while(*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
		p++;
	c.json = p;
}

Result Parser::ParseNull(Context& c, Value& v) {
	Expect(c, 'n');
	if(c.json[0] != 'u' || c.json[1] != 'l' || c.json[2] != 'l')
		return kParseInvalidValue;
	c.json += 3;
	v.type = kNull;
	return kParseOk;
}

Result Parser::ParseTrue(Context& c, Value& v) {
	Expect(c, 't');
	if(c.json[0] != 'r' || c.json[1] != 'u' || c.json[2] != 'e')
		return kParseInvalidValue;
	c.json += 3;
	v.type = kTrue;
	return kParseOk;
}

Result Parser::ParseFalse(Context& c, Value& v) {
	Expect(c, 'f');
	if(c.json[0] != 'a' || c.json[1] != 'l' || c.json[2] != 's' || c.json[3] != 'e')
		return kParseInvalidValue;
	c.json += 4;
	v.type = kFalse;
	return kParseOk;
}


}
