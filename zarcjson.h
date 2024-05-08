#pragma once

#include <iostream>
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
};


struct Value {
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

private:
    Parser();
    static ParserPtr parser_;

private:
    void ParseWhitespace(Context& c);
    Result ParseNull(Context& c, Value& v);
    Result ParseValue(Context& c, Value& v);
    Result ParseTrue(Context& c, Value& v);
    Result ParseFalse(Context& c, Value& v);
};

}

