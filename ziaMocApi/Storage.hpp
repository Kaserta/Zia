//
// Created by azkalaak on 11/01/2020.
//

#ifndef SALUT_STORAGE_HPP
#define SALUT_STORAGE_HPP

#include <map>

template <typename T>
class Storage : public std::map<T, T> {
public:
    Storage(std::map<T, T> &) {} // assignate the defaults values
    void reset(); //reset the value to the defaults ones
    void load(std::string &path); // load the values from file

private:
    std::map<T, T> m_defaultState;

};

#endif //SALUT_STORAGE_HPP
