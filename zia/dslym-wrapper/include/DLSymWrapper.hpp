//
// Created by azkalaak on 29/01/2020.
//

#ifndef ZIA_DLSYMWRAPPER_HPP
#define ZIA_DLSYMWRAPPER_HPP

#include "dlfcn.h"
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

        DLSymWrapper &operator<<(const std::filesystem::path &path);

    private:
        template<typename T, typename ...Args>
        std::function<T(Args...)> getFunction(const std::string &symbol);

        void loadLibrary(const std::filesystem::path &path);

        std::filesystem::path m_path = "";
        void *m_loadedLibrary = nullptr;
    };

    // --------------- TEMPLATE IMPLEMENTATION -----------------

    template<typename T, typename ...Args>
    std::function<T(Args...)> DLSymWrapper::getFunction(const std::string &symbol)
    {
        size_t ret = 0;
        T (*tmp)(Args...);

        if (!m_loadedLibrary)
            std::cerr << "WHAT ARE YOUR DOING YOU MORON?" << std::endl;
        ret = (size_t) dlsym(m_loadedLibrary, symbol.c_str());

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
        ret = (T *)dlsym(m_loadedLibrary, symbol.c_str());
        if (!ret) {
            std::cerr << "SYMBOL DOES NOT EXIST!" << std::endl;
            throw std::exception();
        }
        return *ret;
    }
}
#endif //ZIA_DLSYMWRAPPER_HPP
