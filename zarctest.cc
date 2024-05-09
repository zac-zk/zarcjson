#include <gtest/gtest.h>
#include "zarcjson.h"

void TestTypeAndResult(zarcjson::Type type, zarcjson::Result result, const char* json) {	
	zarcjson::Value v;
	v.type = zarcjson::Type::kTrue;
	zarcjson::Parser::ParserPtr parser = zarcjson::Parser::get_instance();
	EXPECT_EQ(result, parser->Parse(v, json));
	EXPECT_EQ(type, parser->get_type(v));
}

void TestNumber(double expect, const char* json) {
    zarcjson::Value v;
    v.type = zarcjson::Type::kTrue;
    zarcjson::Parser::ParserPtr parser = zarcjson::Parser::get_instance();
    EXPECT_EQ(zarcjson::Result::kParseOk, parser->Parse(v, json));
    EXPECT_EQ(zarcjson::Type::kNumber, parser->get_type(v));
    EXPECT_EQ(expect, parser->get_number(v));
}

TEST(SingletonTest, BasicTest) {
	EXPECT_EQ(zarcjson::Parser::get_instance(), zarcjson::Parser::get_instance());
}

TEST(ParseNullTest, BasicTest) {
	TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseOk, "null");
}

TEST(ParseTrueTest, BasicTest) {
	TestTypeAndResult(zarcjson::Type::kTrue, zarcjson::Result::kParseOk, "true");
}

TEST(ParseFalseTest, BasicTest) {
	TestTypeAndResult(zarcjson::Type::kFalse, zarcjson::Result::kParseOk, "false");
}

TEST(ParseNumberTest, BasicTest) {
    TestNumber(0.0, "0");
    TestNumber(0.0, "-0");
    TestNumber(0.0, "-0.0");
    TestNumber(1.0, "1");
    TestNumber(-1.0, "-1");
    TestNumber(1.5, "1.5");
    TestNumber(-1.5, "-1.5");
    TestNumber(3.1416, "3.1416");
    TestNumber(0E10, "0E10");
    TestNumber(0e10, "0e10");
    TestNumber(1E10, "1E10");
    TestNumber(1e10, "1e10");
    TestNumber(1E+10, "1E+10");
    TestNumber(1E-10, "1E-10");
    TestNumber(-1E10, "-1E10");
    TestNumber(-1e10, "-1e10");
    TestNumber(-1E+10, "-1E+10");
    TestNumber(-1E-10, "-1E-10");
    TestNumber(1.234E+10, "1.234E+10");
    TestNumber(1.234E-10, "1.234E-10");
    TestNumber(0.0, "1e-10000");
    TestNumber(0.0, "-0.0");
    TestNumber(1.0, "1");
    TestNumber(-1.0, "-1");
    TestNumber(1.5, "1.5");
    TestNumber(-1.5, "-1.5");
    TestNumber(3.1416, "3.1416");
    TestNumber(1E10, "1E10");
    TestNumber(1e10, "1e10");
    TestNumber(1E+10, "1E+10");
    TestNumber(1E-10, "1E-10");
    TestNumber(-1E10, "-1E10");
    TestNumber(-1e10, "-1e10");
    TestNumber(-1E+10, "-1E+10");
    TestNumber(-1E-10, "-1E-10");
    TestNumber(1.234E+10, "1.234E+10");
    TestNumber(1.234E-10, "1.234E-10");
    TestNumber(0.0, "1e-10000");
}

TEST(ParseExpectValue, BasicTest) {
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseExpectValue, "");
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseExpectValue, " ");
}

TEST(ParseInvalidValueTest, BasicTest) {
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseInvalidValue, "nul");
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseInvalidValue, "?");
    
    // invalid number
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseInvalidValue, "+0");
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseInvalidValue, "+1");
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseInvalidValue, ".123");
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseInvalidValue, "1.");
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseInvalidValue, "INF");
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseInvalidValue, "inf");
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseInvalidValue, "NAN");
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseInvalidValue, "nan");
    
}

TEST(ParseRootNotSigularTest, BasicTest) {
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseRootNotSigular, "null x");
   
    // invalid number
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseRootNotSigular, "0123");
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseRootNotSigular, "0x0");
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseRootNotSigular, "0x123");
}

TEST(ParseNumberTooBig, BasicTest) {

    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseNumberTooBig, "1e309");
    TestTypeAndResult(zarcjson::Type::kNull, zarcjson::Result::kParseNumberTooBig, "-1e309");
}

