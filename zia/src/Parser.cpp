//
// Created by Yunn Xairou on 11/02/2020.
//

#include "Parser.hpp"

#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

std::map<std::string, std::string> Parser::parse(const std::string &file) const noexcept
{
    std::ifstream stream(file.c_str());
    std::string ext = file.substr(file.find_last_of(".") + 1);
    std::string content((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    try {
        if (ext == "json") return getJson(content);
        if (ext == "ini") return getIni(file);
    } catch (...) { /* */ }

    return std::map<std::string, std::string>();
}

/*
 * INI PARSING
 */

#include "INIParser.h"
#include <vector>

std::map<std::string, std::string> Parser::getIni(const std::string &document) const
{
    cppiniparser::INIConfig config = cppiniparser::INIParser::Read(document);
    std::vector<std::string> sections = config.Sections();
    std::vector<std::string>::const_iterator s = sections.begin();

    std::map<std::string, std::string> result;

    for (; s != sections.end(); ++s) {
        std::vector<std::string> opts = config.Options(*s);
        std::vector<std::string>::const_iterator o = opts.begin();

        for (; o != opts.end(); ++o) {
            std::string key = *s + '.' + *o;
            std::string value = config.GetOption(*s, *o);

            result.insert(std::pair<std::string, std::string>(key, value));
        }
        std::cout << std::endl;
    }

    return result;
}

/*
 * JSON PARSING
 */

static const enum { e_Null, e_False, e_True, e_Object, e_Array, e_String, e_Number };

std::map<std::string, std::string> Parser::getJson(const std::string &json) const noexcept
{
    rapidjson::Document document;
    std::map<std::string, std::string> result;

    if (!document.Parse(json.c_str()).HasParseError() && document.IsObject())
        for (auto itr = document.MemberBegin(); itr != document.MemberEnd(); ++itr) {
            if (itr->value.GetType() != e_Object)
                result.insert(std::pair<std::string, std::string>(itr->name.GetString(), getJsonValue(itr->value)));
            else
                result.merge(getJsonObject(itr->name.GetString(), itr->value));
        }
    return result;
}

std::map<std::string, std::string> Parser::getJsonObject(const std::string &section, const rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &document) const noexcept
{
    std::map<std::string, std::string> result;

    for (auto itr = document.MemberBegin(); itr != document.MemberEnd(); ++itr) {
        std::string key = std::string(section.c_str()) + '.' + itr->name.GetString();

        if (itr->value.GetType() != e_Object)
            result.insert(std::pair<std::string, std::string>(key, getJsonValue(itr->value)));
        else
            result.merge(getJsonObject(key, itr->value));
    }
    return result;
}

std::string Parser::getJsonValue(const rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &value) const noexcept
{
    std::stringstream arr;

    switch (value.GetType()) {
        case e_False:
        case e_True:
            return value.GetBool() ? "true" : "false";
        case e_String:
            return value.GetString();
        case e_Number:
            return value.IsInt() ? std::to_string(value.GetInt()) : std::to_string(value.GetDouble());
        case e_Array:
            for (auto &a : value.GetArray()) {
                if (arr.str().length() > 1)
                    arr << ":";
                arr << getJsonValue(a);
            }
            return arr.str();
        case e_Object:
            arr << "{";
            for (auto itr = value.MemberBegin(); itr != value.MemberEnd(); ++itr) {
                if (arr.str().length() > 1)
                    arr << ", ";
                if (itr->value.GetType() == e_String)
                    arr << "\"" << itr->name.GetString() << "\": \"" << getJsonValue(itr->value) << "\"";
                else if (itr->value.GetType() == e_Null)
                    arr << "\"" << itr->name.GetString() << "\": null";
                else
                    arr << "\"" << itr->name.GetString() << "\": " << getJsonValue(itr->value);
            }
            arr << "}";
            return arr.str();
    }
    return "";
}
