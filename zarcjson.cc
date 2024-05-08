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
		case 'n': return ParseLiteral(c, v, "null", kNull);
		case 't': return ParseLiteral(c, v, "true", kTrue);
		case 'f': return ParseLiteral(c, v, "false", kFalse);
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

Result Parser::ParseLiteral(Context& c, Value& v, const char* s, Type type) {
    size_t i;
    Expect(c, s[0]);
    for(i = 0;s[i+1]!='\0';i++) {
        if(c.json[i] != s[i+1])
            return kParseInvalidValue;
    }
    c.json += i;
    v.type = type;
    return kParseOk;
}

}
