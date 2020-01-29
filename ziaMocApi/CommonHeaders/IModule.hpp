//
// Created by azkalaak on 11/01/2020.
//

#ifndef ZIA_TEMPO_IMODULE_HPP
#define ZIA_TEMPO_IMODULE_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Storage.hpp"

class IModule {
public:
    virtual ~IModule() = default;

    //virtual IModule &operator<<(std::string &);
    virtual const std::string &getName() = 0;
    //virtual IModule &operator>>(std::string &);
};

class AModule : public IModule {
public:
    explicit AModule(std::string name) {m_name = name;}
    ~AModule() override = default;

    std::shared_ptr<std::string> &loadConfig(const std::string &filePath) {
        std::cout << m_name << ": loading config from: " << filePath << std::endl;
        return m_gestConfig;
    };
    const std::string &getName() override {return m_name;}
    AModule &operator<<(std::string &);

    AModule &operator>>(std::string &);

protected:
    std::string m_name = "module pas initialisé";
    std::shared_ptr<std::string> m_gestConfig;
private:
    void entry(const std::string &str);

    void output(std::string &buffer);


    std::map<std::string, std::string> m_storage;
};

std::string operator<<(std::string &, IModule &);

std::string operator>>(std::string &, IModule &);

class Mediator {
public:
    Mediator();
    ~Mediator() = default;
    void setUpConf(std::pair<std::shared_ptr<IModule>, std::shared_ptr<std::string>>);

private:
    std::string m_name = "[Mediator]";
    std::vector<std::shared_ptr<IModule>> m_modules;
};

class Html : public AModule {
public:
    Html(): AModule("Html") {}
    ~Html() override = default;
};

class Http : public AModule {
public:
    Http(): AModule("Http") {}
    ~Http() override = default;
};

class PhpCGI : public AModule {
public:
    PhpCGI(): AModule("PhpCGI") {}
    ~PhpCGI() override  = default;
};

class SSLRequest : public AModule {
public:
    SSLRequest(): AModule("SSLRequest") {}
    ~SSLRequest() override = default;
};



#endif //ZIA_TEMPO_IMODULE_HPP
