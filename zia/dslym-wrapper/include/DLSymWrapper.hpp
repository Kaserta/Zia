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
        std::function<T(Args...)> getSymbol(const std::string &symbol);

        DLSymWrapper &operator<<(const std::filesystem::path &path);

    private:
        void loadLibrary(const std::filesystem::path &path);

        std::filesystem::path m_path = "";
        void *m_loadedLibrary = nullptr;
    };

    template <typename T, typename ...Args>
    std::function<T(Args...)> DLSymWrapper::getSymbol(const std::string &symbol)
    {
        size_t ret = 0;
        T(*tmp)(Args...);

        if (!m_loadedLibrary)
            std::cerr << "WHAT ARE YOUR DOING YOU MORON?" << std::endl;
        ret = (size_t)dlsym(m_loadedLibrary, symbol.c_str());

        if (!ret)
            std::cerr << "NO SYMBOL FOUND!!!" << std::endl;
        T (**temp)(Args...) = &tmp;
        auto *ptr = (size_t *)temp;
        *ptr = ret;
        return std::function<T(Args...)>(tmp);
    }
}

#endif //ZIA_DLSYMWRAPPER_HPP
