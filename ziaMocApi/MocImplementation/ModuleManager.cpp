//
// Created by azkalaak on 21/01/2020.
//

#include <utility>
#include <iostream>
#include "ModuleManager.hpp"

ModuleManager::ModuleManager(std::string path) : m_pathToConf(std::move(path))
{
    std::cout << m_name << ": created" << std::endl;
    std::cout << m_name << ": configuration file is: " << path << std::endl;
    std::cout << m_name << ": doing a fake parsing of the conf file" << std::endl;

    std::cout << m_name << ": 4 modules recognized!" << std::endl;
    m_moduleList.emplace_back("./modules/moduleOpenSSL.json");
    m_moduleList.emplace_back("./modules/modulePHP.xml");
    m_moduleList.emplace_back("./modules/moduleHTTP.json");
    m_moduleList.emplace_back("./modules/moduleHTML.ini");
    for (auto &i : m_moduleList)
        std::cout << m_name << ": the following conf exists (and module): " << i << std::endl;
}

void ModuleManager::createMediator()
{
    std::cout << m_name << ": creating mediator!" << std::endl;
    m_mediator = std::make_shared<Mediator>();
}