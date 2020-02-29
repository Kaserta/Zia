/*
** EPITECH PROJECT, 2020
** UriParser
** File description:
** UriParser
*/

#ifndef URIPARSER_HPP_
#define URIPARSER_HPP_

#include <iostream>
#include <map>
#include <vector>
#include <sstream>

class UriParser {
    public:
        const static std::vector<std::string> /*std::map<std::string, std::string>*/ parse(const std::string &to_parse) noexcept;
        static std::string split(const std::string &to_parse, const char &c = ' ', int pos = 0) noexcept;
    private:
        UriParser();
        ~UriParser();
};

#endif /* !URIPARSER_HPP_ */
