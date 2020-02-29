#include <gtest/gtest.h>
#include "Parser.hpp"

TEST(parsing_tests, stress_tests)
{
    Parser p;
    std::map<std::string, std::string> empty =  p.parse("idonotexist");

    ASSERT_TRUE(empty.empty());
}

TEST(parsing_tests, json)
{
    Parser p;
    std::map<std::string, std::string> json =  p.parse("example.json");

    ASSERT_EQ(json.size(), 14);

    ASSERT_EQ(json.at("hello"), "world");
    ASSERT_EQ(json.at("t"), "true");
    ASSERT_EQ(json.at("f"), "false");
    ASSERT_EQ(json.at("n"), "");
    ASSERT_EQ(json.at("i"), "123");
    ASSERT_EQ(json.at("pi"), "3.141600");
    ASSERT_EQ(json.at("a"), "1:2:3:4:5");


    ASSERT_EQ(json.at("o.n"), "");
    ASSERT_EQ(json.at("o.a"), "1:2:3:4:5");
}

TEST(parsing_tests, ini)
{
    Parser p;
    std::map<std::string, std::string> ini =  p.parse("example.ini");

    ASSERT_EQ(ini.size(), 2);

    ASSERT_EQ(ini.at("Section.key3"), "value3");
    ASSERT_EQ(ini.at("Section.key4"), "value4");
}