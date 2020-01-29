//
// Created by azkalaak on 29/01/2020.
//

#include <dlfcn.h>
#include <iostream>
#include "DLSymWrapper.hpp"

using namespace Zia::Library;

DLSymWrapper::~DLSymWrapper()
{
    if (m_loadedLibrary)
        dlclose(m_loadedLibrary);
}

void DLSymWrapper::loadLibrary(const std::filesystem::path &path)
{
    if (m_loadedLibrary)
        dlclose(m_loadedLibrary);
    m_loadedLibrary = dlopen(path.c_str(), RTLD_LAZY);
    if (!m_loadedLibrary)
        std::cerr << "ADD EXCEPTION THERE: " << dlerror() << std::endl;
}



DLSymWrapper &DLSymWrapper::operator<<(const std::filesystem::path &path)
{
    loadLibrary(path);
    return *this;
}