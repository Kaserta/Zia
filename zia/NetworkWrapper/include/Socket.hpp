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
        friend class PollWrap;
    public:
        explicit Socket(sockType, bool isV6 = false);
        explicit Socket(int sockFd);
        Socket(const Socket &) = delete;

        void bind(int port);
        void listen(int queueNumber = 1);
        void write(const std::string &buffer);
        void read(std::string &buffer, size_t sizeToRead);
        std::shared_ptr<Socket> accept();

        ~Socket();
    private:
        int m_socketFd = -1;
        int m_ipVersion = 0;
        struct sockaddr_in s = {0};
    };
}

#endif /* !SOCKET_HPP_ */
