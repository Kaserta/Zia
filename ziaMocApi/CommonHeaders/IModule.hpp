//
// Created by azkalaak on 11/01/2020.
//

#ifndef ZIA_TEMPO_IMODULE_HPP
#define ZIA_TEMPO_IMODULE_HPP

#include <string>
#include <vector>
#include <memory>
#include "Storage.hpp"

class IModule {
public:
    virtual ~IModule() = default;

    IModule &operator<<(std::string &);

    IModule &operator>>(std::string &);
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

class Mediator {
public:
    Mediator();
    ~Mediator() = default;

private:
    std::string m_name = "[Mediator]";
    std::vector<std::shared_ptr<IModule>> m_modules;
};

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
