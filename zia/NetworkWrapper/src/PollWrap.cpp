//
// Created by azkalaak on 09/02/2020.
//

#include "PollWrap.hpp"

using namespace Zia::Network;

void PollWrap::addToWatch(const std::shared_ptr<Socket>& socket, pollFunc func, short events)
{
    struct pollfd pollStruct = {.fd = socket->getFD(), .events = events, .revents = 0};
    m_socketStorage.emplace_back(socket, std::move(func), events, pollStruct);
}

void PollWrap::removeFromWatch(const std::shared_ptr<Socket>& socket)
{
    for (auto i = m_socketStorage.begin(); i != m_socketStorage.end(); ++i) {
        if (std::get<0>(*i) == socket) {
            auto j = i;
            ++i;
            m_socketStorage.erase(j);
            --i;
        }
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
                if (std::get<0>(j)->getFD() == ptr[i].fd && std::get<2>(j) == ptr[i].events)
                    std::get<1>(j)(std::get<0>(j), std::get<2>(j));
            }
        }
        delete[] ptr;
    }
}