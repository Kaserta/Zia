/*
** EPITECH PROJECT, 2020
** Socket
** File description:
** Socket in c++
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

namespace Zia::Network {
    enum sockType {TCP = 0, UDP = 1};
    class Socket {
    public:
        Socket(sockType, bool isV6 = false);
        Socket(const Socket &) = delete;

        ~Socket();
    private:
        int m_socketFd = -1;
    };
}

#endif /* !SOCKET_HPP_ */
