/*
** EPITECH PROJECT, 2019
** CallAPI
** File description:
** CallAPI
*/

#include "CallAPI.hpp"

CallAPI::CallAPI()
{
    LoadPaths();
    LoadLibs();
}

void CallAPI::LoadPaths()
{
    if (!names.empty())
        names.clear();
    for (auto &p: std::filesystem::recursive_directory_iterator(RESSOURCE_PATH"shared_libraries"))
        if (p.path().extension() == DYNLIB_EXT)
            this->names.push_back(p.path().filename());
}

void CallAPI::LoadLibs()
{
    if (!libs.empty())
        libs.clear();
    dynamic_lib_handle h;
    std::function<unsigned int(void)>i;
    for (auto &p : names) {
        std::string path = RESSOURCE_PATH"shared_libraries/";
        path+=p;
        if ((h = dlopen(path.c_str(), RTLD_NOW)) != nullptr) {
            auto toto = std::make_shared<dynamic_lib>(path, h);
            i = load<unsigned int(void)>("getID", h);
            libs.insert({i(), toto});
            MobID.push_back(i());
        }
    }
}
