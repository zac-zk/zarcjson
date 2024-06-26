#pragma once

#include <memory>

namespace zarcjson {

enum Type {
    kNull,
    kTrue,
    kFalse,
    kNumber,
    kString,
    kArray,
    kObject
};

enum Result {
    kParseOk = 0,
    kParseExpectValue,
    kParseInvalidValue,
    kParseRootNotSigular,
    kParseNumberTooBig,
};


struct Value {
    double n;
    Type type;
};

struct Context {
    const char* json;
};

class Parser {
public:
    using ParserPtr = std::shared_ptr<Parser>;

    ~Parser();
    Parser(Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    static ParserPtr get_instance();

public:
    Type get_type(const Value& v);
    Result Parse(Value& v, const char* json);
    double get_number(const Value& v);

private:
    Parser();
    static ParserPtr parser_;

private:
    Result ParseValue(Context& c, Value& v);
    void ParseWhitespace(Context& c);
    Result ParseLiteral(Context& c, Value& v, const char* s, Type type);
    Result ParseNumber(Context& c, Value& v);
};

}

