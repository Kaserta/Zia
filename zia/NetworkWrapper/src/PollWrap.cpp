//
// Created by azkalaak on 09/02/2020.
//

#include "PollWrap.hpp"
#if _WIN32
#include <winsock2.h>
#include <windows.h>
#define poll WSAPoll
#endif
using namespace Zia::Network;

void PollWrap::addToWatch(const std::shared_ptr<Socket>& socket, pollFunc func, short events)
{
    struct pollfd pollStruct = {0};
    pollStruct.events = events;
    pollStruct.revents = 0;
    pollStruct.fd = socket->m_socketFd;
    m_socketStorage.emplace_back(socket, std::move(func), events, pollStruct);
}

void PollWrap::removeFromWatch(const std::shared_ptr<Socket>& socket)
{
    for (auto i = m_socketStorage.begin(); i != m_socketStorage.end(); ++i) {
        if (std::get<0>(*i) == socket) {
            m_socketStorage.erase(i);
            i = m_socketStorage.begin();
        }
        if (i == m_socketStorage.end())
            break;
    }
}

void PollWrap::start()
{
    while (true) {
        if (m_socketStorage.empty()) // if empty no need to watch
            return;

        auto *ptr =  new struct pollfd [m_socketStorage.size()];
        size_t i = 0;
        size_t size = m_socketStorage.size();

        for (auto &j : m_socketStorage)
            ptr[i++] = std::get<3>(j);

        auto number = poll(ptr, size, -1);
        if (number == -1)
            return;
        for (i = 0; i < size && number; ++i) {
            if (ptr[i].revents == 0)
                continue;
            --number;
            for (auto &j : m_socketStorage) {
                if (std::get<0>(j)->m_socketFd == ptr[i].fd && std::get<2>(j) == ptr[i].events)
                    std::get<1>(j)(std::get<0>(j), std::get<2>(j));
            }
        }
        delete[] ptr;
    }
}