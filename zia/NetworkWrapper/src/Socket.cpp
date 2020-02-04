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
#pragma comment(lib,"ws2_32.lib")
#define CLOSE_SOCK(sock) closesocket(sock)
[[constructor]]
void winSockStartup()
{
    WSAStartup(MAKEWORD(2,2),&amp;wsa);
}

[[destructor]]
void winSockCleanup()
{
    WSACleanup();
}
#else
// -------------- Linux ------------------
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define CLOSE_SOCK(sock) close(sock)
#endif

#include "ZiaExceptions.hpp"
#include "Socket.hpp"

using namespace Zia::Network;

Socket::Socket(sockType protocol, bool isV6)
{
    int ipVersionType = AF_INET;

    if (isV6)
        ipVersionType = AF_INET6;
    m_socketFd = TCP ? socket(ipVersionType, SOCK_STREAM, IPPROTO_TCP) : socket(ipVersionType, SOCK_DGRAM, IPPROTO_UDP);
    if (m_socketFd <= 0)
        throw Zia::Exceptions::NetworkException("Socket could not be created");
}

Socket::~Socket()
{
    if (m_socketFd > 0)
        CLOSE_SOCK(m_socketFd);
}