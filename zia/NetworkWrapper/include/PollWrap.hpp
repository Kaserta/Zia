//
// Created by azkalaak on 09/02/2020.
//

#ifndef ZIA_POLLWRAP_HPP
#define ZIA_POLLWRAP_HPP

#if _WIN32
#include <windows.h>
#else
#include <poll.h>
#endif

#include <memory>
#include <functional>
#include <map>
#include "Socket.hpp"

namespace Zia::Network {
    typedef std::function<void(std::shared_ptr<Socket>, short)> pollFunc;
    class PollWrap {
    public:
        PollWrap() = default;
        ~PollWrap() = default;

        void addToWatch(const std::shared_ptr<Socket>&, pollFunc, short);
        void removeFromWatch(const std::shared_ptr<Socket>&);

        void start();
    private:
        std::vector<std::tuple<std::shared_ptr<Socket>, pollFunc, short, struct pollfd>> m_socketStorage;
    };
}

#endif //ZIA_POLLWRAP_HPP
