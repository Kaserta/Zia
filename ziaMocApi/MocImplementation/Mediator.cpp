//
// Created by azkalaak on 21/01/2020.
//

#include <iostream>
#include "IModule.hpp"

Mediator::Mediator()
{
    std::cout << m_name << ": created" << std::endl;
}


void Mediator::setUpConf(std::pair<std::shared_ptr<IModule>, std::shared_ptr<std::string>> moduleConfig)
{
    std::cout << m_name << ": " << moduleConfig.first->getName() << ": configuration loaded." << std::endl;
}