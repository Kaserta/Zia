//
// Created by azkalaak on 21/01/2020.
//

#ifndef SALUT_MODULEMANAGER_HPP
#define SALUT_MODULEMANAGER_HPP

#include <string>
#include <vector>
#include "IModule.hpp"

class ModuleManager {
public:
    ModuleManager(std::string pathToConf);

private:
    void threadMoc();
    void loadModules();
    void createMediator();

    std::string m_pathToConf;
    std::string m_name = "[ModuleManager]";
    std::vector<std::string> m_moduleList;
    std::vector<AModule> m_modules;
    std::shared_ptr<Mediator> m_mediator;
};

#endif //SALUT_MODULEMANAGER_HPP
