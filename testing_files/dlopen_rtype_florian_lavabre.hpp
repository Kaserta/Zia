/*
** EPITECH PROJECT, 2019
** CallAPI
** File description:
** CallAPI
*/

#ifndef CALLAPI_HPP_
#define CALLAPI_HPP_

#ifdef __gnu_linux__
    #include <dlfcn.h>
#endif
#include <iostream>
#include <filesystem>
#include <functional>
#include "../Utils/Utils.hpp"
#include "../Exception/Exceptions.hpp"

typedef void * dynamic_lib_handle;

struct dynamic_lib {
    dynamic_lib(const std::string &p, dynamic_lib_handle handler) : path(p), handler(handler) {}
    ~dynamic_lib() {
        if (handler != nullptr)
            dlclose(handler);
    }
    std::string path;
    dynamic_lib_handle handler;
    dynamic_lib_handle get_handler() {return handler;};
};

class CallAPI {
	public:
        static CallAPI &get() {static CallAPI hey; return hey;}
        std::vector<unsigned int> GetIDS() {return this->MobID;}
        std::string getSpriteByName(const std::string &s) {
            for (auto lib = libs.begin(); lib != libs.end(); lib++) {
                std::function<const char *(void)>n = load<const char *(void)>("getName", lib->second->get_handler());
                std::function<const char *(void)>pat = load<const char *(void)>("getSprite", lib->second->get_handler());
                std::string p(n());
                if (p == s)
                    return pat();
            }
            throw Exceptions::NoLibExceptionName();
        }
        std::string getSpriteByID(unsigned int i) {
            for (auto lib = libs.begin(); lib != libs.end(); lib++) {
                std::function<unsigned int (void)>id = load<unsigned int (void)>("getID", lib->second->get_handler());
                std::function<const char *(void)>pat = load<const char *(void)>("getSprite", lib->second->get_handler());
                if (id() == i)
                    return std::string(pat());
            }
            throw Exceptions::NoLibExceptionSprite();
        }
        unsigned int getIdByName(const std::string &s) {
            for (auto lib = libs.begin(); lib != libs.end(); lib++) {
                std::function<const char *(void)>n = load<const char * (void)>("getName", lib->second->get_handler());
                std::function<unsigned int (void)>id = load<unsigned int (void)>("getID", lib->second->get_handler());
                if (n() == s)
                    return id();
            }
            throw Exceptions::NoLibExceptionID();
        }
        template <typename T>
        std::shared_ptr<T> getMobInfo(unsigned int id)
        {
            std::function<const char *(void)>n = load<const char *(void)>("getName", libs[id]->get_handler());
            std::function<const char *(void)>path = load<const char *(void)>("getSprite", libs[id]->get_handler());
            std::function<bool(void)>anim = load<bool(void)>("isAnimated", libs[id]->get_handler());
            std::function<bool(void)>sla = load<bool(void)>("isSlave", libs[id]->get_handler());
            std::function<unsigned int (void)>liv = load<unsigned int (void)>("getLives", libs[id]->get_handler());
            std::function<unsigned int (void)>shot = load<unsigned int (void)>("getShots", libs[id]->get_handler());
            std::function<unsigned int (void)>freq = load<unsigned int (void)>("getShotFrequency", libs[id]->get_handler());
            std::function<unsigned int (void)>spesho = load<unsigned int (void)>("getShotSpeed", libs[id]->get_handler());
            std::function<float (void)>sizeX = load<float (void)>("getSizeX", libs[id]->get_handler());
            std::function<float (void)>sizeY = load<float (void)>("getSizeY", libs[id]->get_handler());
            std::function<float (void)>scaling = load<float (void)>("getScale", libs[id]->get_handler());
            std::shared_ptr<T> mob = std::make_shared<T>(id, std::string(n()));
            mob->setLives(liv());
            /*mob->setPath(path());
            mob->setIsAnimated(anim())
            mob->setSlave(sla())
            mob->setShots(shot());
            mob->setShot_frequency(freq());
            mob->setShot_speed(spesho());
            mob->setSizeX(sizeX())
            mob->setSizeY(sizeY())
            */return mob;
        }
	private:
		CallAPI();
        void LoadPaths();
        void LoadLibs();
        template<class T>
        std::function<T> load(const std::string &symbol, dynamic_lib_handle _handle) {
            char *error;
            dlerror();
            void* result = dlsym(_handle, symbol.c_str());
            if ((error = dlerror()))
                throw std::logic_error(error);
            return reinterpret_cast<T*>(result);
        }
        std::map<unsigned int, std::shared_ptr<dynamic_lib>> libs;
        std::vector<std::string> names;
        std::vector<unsigned int> MobID;
};
#endif /* !CALLAPI_HPP_ */
