//
// Created by Yunn Xairou on 11/02/2020.
//

#ifndef ZIA_PARSER_HPP
#define ZIA_PARSER_HPP

#include <map>
#include "rapidjson/document.h"

class Parser {
public:
    std::map<std::string, std::string> parse(std::string) const noexcept;

private:
    std::map<std::string, std::string> getJson(std::string json) const noexcept;
    std::string getJsonValue(const rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &value) const noexcept;
};


#endif //ZIA_PARSER_HPP
