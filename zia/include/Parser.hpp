//
// Created by Yunn Xairou on 11/02/2020.
//

#ifndef ZIA_PARSER_HPP
#define ZIA_PARSER_HPP

#include <map>
#include "rapidjson/document.h"

class Parser {
public:
    std::map<std::string, std::string> parse(const std::string &) const noexcept;

private:

    /* JSON */
    std::map<std::string, std::string> getJson(const std::string &) const noexcept;
    std::map<std::string, std::string> Parser::getJsonObject(const std::string &section, const rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &value) const noexcept;
    std::string getJsonValue(const rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &value) const noexcept;
};


#endif //ZIA_PARSER_HPP
