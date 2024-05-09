#include "zarcjson.h"
#include "assert.h"
#include "stdlib.h"
#include "errno.h"
#include "math.h"
#include <cerrno>
#include <cmath>

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

double Parser::get_number(const Value& v) {
    assert(v.type == kNumber);
    return v.n;
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
		if(*c.json != '\0') {
            ret = kParseRootNotSigular;
            v.type = kNull;
        }
	}
	return ret;
}

Result Parser::ParseValue(Context& c, Value& v) {
	switch (*c.json) {
    case 'n': return ParseLiteral(c, v, "null", kNull);
    case 't': return ParseLiteral(c, v, "true", kTrue);
    case 'f': return ParseLiteral(c, v, "false", kFalse);
    case '\0': return kParseExpectValue;
    default: return ParseNumber(c, v);
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

inline bool IsDigit(const char ch) {
    return ch >= '0' && ch <= '9';
}

inline bool IsDigit1To9(const char ch) {
    return ch >= '1' && ch <= '9';
}

Result Parser::ParseNumber(Context& c, Value& v) {
    const char* p = c.json;
    if(*p == '-') p++;
    if(*p == '0') p++;
    else {
        if(!IsDigit1To9(*p)) return kParseInvalidValue;
        for(p++;IsDigit(*p);p++);
    }
    if(*p == '.') {
        p++;
        if(!IsDigit(*p)) return kParseInvalidValue;
        for(p++;IsDigit(*p);p++);
    }
    if(*p == 'e' || *p == 'E') {
        p++;
        if(*p == '+' || *p == '-') p++;
        if(!IsDigit(*p)) return kParseInvalidValue;
        for(p++;IsDigit(*p);p++);
    }
    errno = 0;
    v.n = strtod(c.json, NULL);
    if(errno == ERANGE && (v.n == HUGE_VAL || v.n == -HUGE_VAL))
        return kParseNumberTooBig;
    v.type = kNumber;
    c.json = p;
    return kParseOk;
}

}
