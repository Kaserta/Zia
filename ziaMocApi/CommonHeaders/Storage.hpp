//
// Created by azkalaak on 11/01/2020.
//

#ifndef SALUT_STORAGE_HPP
#define SALUT_STORAGE_HPP

#include <map>

class Storage : public std::map<std::string, std::string> {
public:
    Storage(std::map<std::string, std::string> &) {} // assignate the defaults values
    void reset(); //reset the value to the defaults ones
    void load(std::string &path); // load the values from file

private:
    std::map<std::string, std::string> m_defaultState;

};

#endif //SALUT_STORAGE_HPP
