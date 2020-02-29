/*
** EPITECH PROJECT, 2020
** AModule
** File description:
** Abstract for Module compliant with api
*/

#ifndef AMODULE_HPP_
#define AMODULE_HPP_

#include "IModule.hpp"

class AModule : public IModule {
    public:
        AModule(const std::string &name, const std::string &version) : _MName(name), _MVersion(version) {}
        virtual ~AModule() {}
        const std::string &getName() const noexcept {return _MName;}
        const std::string &getVersion() const noexcept {return _MVersion;}

    protected:
        const std::string &_MName;
        const std::string &_MVersion;
};

#endif /* !AMODULE_HPP_ */
