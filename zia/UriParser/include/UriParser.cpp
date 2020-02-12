/*
** EPITECH PROJECT, 2020
** UriParser
** File description:
** UriParser
*/

#include "UriParser.hpp"

const std::vector<std::string>/*std::map<std::string, std::string>*/ UriParser::parse(const std::string &to_parse)
{
    std::vector<std::string> strings;
    std::istringstream f(to_parse);
    std::string s;
    while (getline(f, s, '\n')) {
        std::cout << s << std::endl;
        strings.push_back(s);
    }
    return strings;
}
