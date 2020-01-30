//
// Created by azkalaak on 29/01/2020.
//

#include <iostream>
#include "DLSymWrapper.hpp"

#ifdef WIN32
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT extern "C"
#endif

using namespace Zia::Library;

DLSymWrapper::~DLSymWrapper()
{
    if (m_loadedLibrary)
        ZIA_CLOSE_LIB(m_loadedLibrary);
}

void DLSymWrapper::loadLibrary(const std::string &path)
{
    std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH: " << path << std::endl;
    if (m_loadedLibrary)
        ZIA_CLOSE_LIB(m_loadedLibrary);
    m_loadedLibrary = ZIA_LOAD_LIB(path.c_str(), RTLD_LAZY);
    if (!m_loadedLibrary)
        std::cerr << "ADD EXCEPTION THERE: " << ZIA_LOAD_ERROR << std::endl;
}



DLSymWrapper &DLSymWrapper::operator<<(const std::string &path)
{
    loadLibrary(path);
    return *this;
}

EXPORT char test = 'c';