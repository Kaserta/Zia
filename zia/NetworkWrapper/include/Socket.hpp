/*
** EPITECH PROJECT, 2020
** Socket
** File description:
** Socket in c++
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include <memory>

namespace Zia::Network {
    enum sockType {TCP = 0, UDP = 1};
    class Socket {
    public:
        explicit Socket(sockType, bool isV6 = false);
        explicit Socket(int sockFd);
        Socket(const Socket &) = delete;

        void bind(int port);
        void listen(int queueNumber = 1);
        std::shared_ptr<Socket> accept();

        int getFD() const { return m_socketFd; }

        ~Socket();
    private:
        int m_socketFd = -1;
        int m_ipVersion = 0;
        struct sockaddr_in s = {0};
    };
}

#endif /* !SOCKET_HPP_ */
