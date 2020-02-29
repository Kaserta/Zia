/*
** EPITECH PROJECT, 2019
** CallAPIWin
** File description:
** CallAPIWin
*/

#include "CallAPIWin.hpp"

CallAPIWin::CallAPIWin()
{
    LoadPaths();
    LoadLibs();
}

void CallAPIWin::LoadPaths()
{
    if (!names.empty())
        names.clear();
    for (auto &p: std::filesystem::recursive_directory_iterator(RESSOURCE_PATH"shared_libraries"))
        if (p.path().extension() == DYNLIB_EXT)
            this->names.push_back(p.path().filename().string());
}

void CallAPIWin::LoadLibs()
{
    if (!libs.empty())
        libs.clear();
    HMODULE h;
    std::function<unsigned int(void)>i;
    for (auto &p : names) {
        std::string path = RESSOURCE_PATH"shared_libraries/";
        path+=p;
        h = LoadLibraryA(path.c_str());
        if (h != nullptr) {
            auto toto = std::make_shared<dynamic_lib>(path, h);
            i = load<unsigned int(void)>("getID", h);
            libs.insert({i(), toto});
            MobID.push_back(i());
        }
    }
}
