//
// Created by azkalaak on 31/01/2020.
//

#ifndef ZIA_ZIAEXCEPTIONS_HPP
#define ZIA_ZIAEXCEPTIONS_HPP
#include <exception>

namespace Zia::Exceptions {
    class ZiaException : public std::exception {
    public:
        explicit ZiaException(const std::string &str) noexcept {m_message = str;}

        [[nodiscard]] const char *what() const noexcept override {return m_message.c_str();}
    private:
        std::string m_message;
    };

    class DLSymWrapperException : public ZiaException {
    public:
        DLSymWrapperException() : ZiaException("[DLSymWrapper]: internal exception.") {}
        explicit DLSymWrapperException(const std::string &str) : ZiaException("[DLSymWrapper]: " + str) {}
    };
}

#endif //ZIA_ZIAEXCEPTIONS_HPP
