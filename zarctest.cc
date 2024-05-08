#include <gtest/gtest.h>
#include "zarcjson.h"

void TestEQ(zarcjson::Type type, zarcjson::Result result, const char* json) {	
	zarcjson::Value v;
	v.type = zarcjson::Type::kTrue;
	zarcjson::Parser::ParserPtr parser = zarcjson::Parser::get_instance();
	EXPECT_EQ(result, parser->Parse(v, json));
	EXPECT_EQ(type, parser->get_type(v));
}

TEST(SingletonTest, BasicTest) {
	EXPECT_EQ(zarcjson::Parser::get_instance(), zarcjson::Parser::get_instance());
}

TEST(ParseNullTest, BasicTest) {
	TestEQ(zarcjson::Type::kNull, zarcjson::Result::kParseOk, "null");
}

TEST(ParseTrueTest, BasicTest) {
	TestEQ(zarcjson::Type::kTrue, zarcjson::Result::kParseOk, "true");
}

TEST(ParseFalseTest, BasicTest) {
	TestEQ(zarcjson::Type::kFalse, zarcjson::Result::kParseOk, "false");
}

TEST(ParseInvalidValueTest, BasicTest) {
	TestEQ(zarcjson::Type::kNull, zarcjson::Result::kParseInvalidValue, "nul");
	TestEQ(zarcjson::Type::kNull, zarcjson::Result::kParseInvalidValue, "?");
}

TEST(ParseRootNotSigularTest, BasicTest) {
	TestEQ(zarcjson::Type::kNull, zarcjson::Result::kParseRootNotSigular, "null x");	
}
