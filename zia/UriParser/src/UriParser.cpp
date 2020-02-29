/*
** EPITECH PROJECT, 2020
** UriParser
** File description:
** UriParser
*/

#include "UriParser.hpp"

const std::vector<std::string>/*std::map<std::string, std::string>*/ UriParser::parse(const std::string &to_parse) noexcept
{
    std::vector<std::string> strings;
    std::istringstream f(to_parse);
    std::string s;
    while (getline(f, s, '\n'))
        strings.push_back(s);
    return strings;
}

std::string UriParser::split(const std::string &to_parse, const char &c, int pos) noexcept
{
    std::vector<std::string> strings;
    std::istringstream f(to_parse);
    std::string s;
    while (getline(f, s, c))
        strings.push_back(s);
    if (pos <= strings.size()-1)
        return strings[pos];
    else
        return "";
}