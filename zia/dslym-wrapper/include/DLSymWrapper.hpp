//
// Created by azkalaak on 29/01/2020.
//

#ifndef ZIA_DLSYMWRAPPER_HPP
#define ZIA_DLSYMWRAPPER_HPP

#ifdef WIN32
#include <windows.h>
#include <windef.h>
#include <atlstr.h>
#define ZIA_LIB HMODULE
#define ZIA_LOAD_LIB(str, useless) LoadLibraryA(str)
#define ZIA_CLOSE_LIB(handle) FreeLibrary(handle)
#define ZIA_LOAD_SYMBOL(handle, str) GetProcAddress(handle, str)
#define ZIA_LOAD_ERROR GetLastError()
#else
#include <dlfcn.h>
#define ZIA_LIB void *
#define ZIA_LOAD_LIB(str, args) dlopen(str, args)
#define ZIA_CLOSE_LIB(handle) dlclose(handle)
#define ZIA_LOAD_SYMBOL(handle, str) dlsym(handle, str)
#define ZIA_LOAD_ERROR dlerror()
#endif

#include <string>
#include <iostream>
#include <filesystem>
#include <functional>

namespace Zia::Library {
    class DLSymWrapper {
    public:
        DLSymWrapper() = default;

        ~DLSymWrapper();

        template<typename T, typename ...Args>
        void getFunction(std::function<T(Args...)> &func, const std::string &symbol);

        template<typename T>
        T &getVariable(const std::string &symbol);

        DLSymWrapper &operator<<(const std::string &path);

    private:
        template<typename T, typename ...Args>
        std::function<T(Args...)> getFunction(const std::string &symbol);

        void loadLibrary(const std::string &path);

        std::filesystem::path m_path = "";
        ZIA_LIB m_loadedLibrary = nullptr;
    };

    // --------------- TEMPLATE IMPLEMENTATION -----------------

    template<typename T, typename ...Args>
    std::function<T(Args...)> DLSymWrapper::getFunction(const std::string &symbol)
    {
        size_t ret = 0;
        T (*tmp)(Args...);

        if (!m_loadedLibrary)
            std::cerr << "WHAT ARE YOUR DOING YOU MORON?" << std::endl;
        ret = (size_t) ZIA_LOAD_SYMBOL(m_loadedLibrary, symbol.c_str());

        if (!ret)
            std::cerr << "NO SYMBOL FOUND!!!" << std::endl;
        T (**temp)(Args...) = &tmp;
        auto *ptr = (size_t *) temp;
        *ptr = ret;
        return std::function<T(Args...)>(tmp);
    }

    template<typename T, typename ... Args>
    void DLSymWrapper::getFunction(std::function<T(Args...)> &func, const std::string &symbol)
    {
        func = getFunction<T, Args...>(symbol);
    }

    template <typename T>
    T &DLSymWrapper::getVariable(const std::string &symbol)
    {
        T *ret = nullptr;

        if (!m_loadedLibrary)
            std::cerr << "ti é fada toi" << std::endl;
        ret = (T *)ZIA_LOAD_SYMBOL(m_loadedLibrary, symbol.c_str());
        if (!ret) {
            std::cerr << "SYMBOL DOES NOT EXIST!" << std::endl;
            throw std::exception();
        }
        return *ret;
    }
}
#endif //ZIA_DLSYMWRAPPER_HPP
