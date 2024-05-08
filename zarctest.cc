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
	zarcjson::Value v;
	v.type = zarcjson::Type::kTrue;
	zarcjson::Parser::ParserPtr parser = zarcjson::Parser::get_instance();
	EXPECT_EQ(zarcjson::Result::kParseOk, parser->Parse(v, "null"));
	EXPECT_EQ(zarcjson::Type::kNull, parser->get_type(v));
}

TEST(ParseTrueTest, BasicTest) {
	zarcjson::Value v;
	v.type = zarcjson::Type::kNull;
	zarcjson::Parser::ParserPtr parser = zarcjson::Parser::get_instance();
	EXPECT_EQ(zarcjson::Result::kParseOk, parser->Parse(v, "true"));
	EXPECT_EQ(zarcjson::Type::kTrue, parser->get_type(v));
}

TEST(ParseFalseTest, BasicTest) {
	zarcjson::Value v;
	v.type = zarcjson::Type::kTrue;
	zarcjson::Parser::ParserPtr parser = zarcjson::Parser::get_instance();
	EXPECT_EQ(zarcjson::Result::kParseOk, parser->Parse(v, "false"));
	EXPECT_EQ(zarcjson::Type::kFalse, parser->get_type(v));
}

TEST(ParseInvalidValueTest, BasicTest) {
	TestEQ(zarcjson::Type::kNull, zarcjson::Result::kParseInvalidValue, "nul");
	TestEQ(zarcjson::Type::kNull, zarcjson::Result::kParseInvalidValue, "?");
}

TEST(ParseRootNotSigularTest, BasicTest) {
	TestEQ(zarcjson::Type::kNull, zarcjson::Result::kParseRootNotSigular, "null x");	
}
