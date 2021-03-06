/*
** EPITECH PROJECT, 2020
** Socket
** File description:
** Socket in c++
*/

// -------------- Windows ----------------
#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#include <cstdlib>
#pragma comment(lib,"ws2_32.lib")
#define CLOSE_SOCK(sock) closesocket(sock)
#define ZIA_SOCKLEN int
#define SEND WSASend
#define MSG_NOSIGNAL 0
namespace Zia::Network {

    void winSockCleanup()
    {
        WSACleanup();
    }

    int winSockStartup() noexcept
    {
        WSADATA wsa;

        WSAStartup(MAKEWORD(2,2),&wsa);
        atexit(winSockCleanup);
        return 0;
    }

    static int internal_useless_variable_to_initialise_winsock_because_i_have_no_choice = winSockStartup();
}
#else
// -------------- Linux ------------------
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define CLOSE_SOCK(sock) close(sock)
#define ZIA_SOCKLEN unsigned int
#endif

#include "ZiaExceptions.hpp"
#include "Socket.hpp"

using namespace Zia::Network;

Socket::Socket(sockType protocol, bool isV6)
{
    m_ipVersion = isV6 ? AF_INET6 : AF_INET;
    m_socketFd = protocol == TCP ? socket(m_ipVersion, SOCK_STREAM, IPPROTO_TCP) : socket(m_ipVersion, SOCK_DGRAM, IPPROTO_UDP);
    if (m_socketFd <= 0)
        throw Zia::Exceptions::NetworkException("Socket could not be created");
}

Socket::Socket(int sockFd)
{
    m_socketFd = sockFd;
    if (m_socketFd <= 0)
        throw  Zia::Exceptions::NetworkException();
}

void Socket::bind(int port)
{
#if _WIN32
    char i = 1;
#else
    int i = 1;
#endif

    s.sin_family = m_ipVersion;
    s.sin_addr.s_addr = INADDR_ANY;
    s.sin_port = htons(port);
    if (::setsockopt(m_socketFd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i)) == -1)
        throw Zia::Exceptions::NetworkException("Setsockopt failed!");
    if (::bind(m_socketFd, (struct sockaddr *) &s, sizeof(s)) == -1)
        throw Zia::Exceptions::NetworkException("Binding failed!");
}

void Socket::listen(int queueNumber)
{
    if (!queueNumber)
        throw Zia::Exceptions::NetworkException("Cannot listen a negative number!");
    ::listen(m_socketFd, queueNumber);
}

void Socket::write(const std::string &buffer)
{
    ::send(m_socketFd, buffer.c_str(), buffer.size(), MSG_NOSIGNAL);
}

// CODE NEW BUFFER / RECUP CHETAFI ONES
void Socket::read(std::string &buffer, size_t sizeToRead)
{
    char *buff = new char[sizeToRead];
    ::recv(m_socketFd, buff, sizeToRead, MSG_NOSIGNAL);
    buffer = buff;
    delete[] buff;
}

std::shared_ptr<Socket> Socket::accept()
{
    ZIA_SOCKLEN len = sizeof(s);
    int newSock = ::accept(m_socketFd, (struct sockaddr *)&s, &len);

    if (newSock < 0)
        throw Zia::Exceptions::NetworkException("Accept error");
    return std::make_shared<Socket>(newSock);
}

Socket::~Socket()
{
    if (m_socketFd > 0)
        CLOSE_SOCK(m_socketFd);
}