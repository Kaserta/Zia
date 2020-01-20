//
// Created by azkalaak on 11/01/2020.
//

#ifndef ZIA_TEMPO_IMODULE_HPP
#define ZIA_TEMPO_IMODULE_HPP

#include <string>

class IModule {
public:
    virtual ~IModule() = default;
};

class AModule : public IModule {
public:
    ~AModule() override = default;

    AModule &operator<<(std::string &);

    AModule &operator>>(std::string &);

private:
    void entry(const std::string &str);

    void output(std::string &buffer);

    Storage m_storage;
};

std::string operator<<(std::string &, AModule &);

std::string operator>>(std::string &, AModule &);

class Http : public AModule {
public:
    ~Http() override = default;
};

class PhpCGI : public AModule {
public:
    ~PhpCGI() override  = default;
};

class SSLRequest : public AModule {
public:
    ~SSLRequest() override = default;
};



#endif //ZIA_TEMPO_IMODULE_HPP
