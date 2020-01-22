//
// Created by azkalaak on 21/01/2020.
//

#include <utility>
#include <iostream>
#include <regex>
#include "ModuleManager.hpp"

ModuleManager::ModuleManager(std::string path) : m_pathToConf(std::move(path))
{
    std::cout << m_name << ": created" << std::endl;
    std::cout << m_name << ": configuration file is: " << m_pathToConf << std::endl;
    std::cout << m_name << ": doing a fake parsing of the conf file" << std::endl;

    std::cout << m_name << ": 4 modules recognized!" << std::endl;
    m_moduleList.emplace_back("./modules/moduleOpenSSL.json");
    m_moduleList.emplace_back("./modules/modulePHP.xml");
    m_moduleList.emplace_back("./modules/moduleHTTP.json");
    m_moduleList.emplace_back("./modules/moduleHTML.ini");
    m_SharedList.emplace_back("./libs/libOpenSSL.so");
    m_SharedList.emplace_back("./libs/libPHP.so");
    m_SharedList.emplace_back("./libs/libHTTP.so");
    m_SharedList.emplace_back("./libs/libHTML.so");
    for (int i =0; i < m_moduleList.size(); i++)
        std::cout << m_name << ": the following conf exists (and module): " << m_moduleList[i] << " --> " << m_SharedList[i] << std::endl;
    createMediator();
    loadModules();
}

void ModuleManager::createMediator()
{
    std::cout << m_name << ": creating mediator" << std::endl;
    m_mediator = std::make_shared<Mediator>();
}

void ModuleManager::loadModules()
{
    std::cout << m_name << ": loading modules from shared library" << std::endl;
    m_modules.emplace_back(std::make_shared<SSLRequest>());
    m_modules.emplace_back(std::make_shared<PhpCGI>());
    m_modules.emplace_back(std::make_shared<Http>());
    m_modules.emplace_back(std::make_shared<Html>());
    for (int i = 0; i < m_modules.size(); ++i) {
        m_mediator->setUpConf(std::pair<std::shared_ptr<IModule>, std::shared_ptr<std::string>>(m_modules[i], m_modules[i]->loadConfig(m_moduleList[i])));
    }
}