/*
** EPITECH PROJECT, 2020
** Socket
** File description:
** Socket in c++
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cassert>
#include <string>
#include <string.h>
#include <sstream>
#include <errno.h>
#include <iostream>
#include <errno.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>

class Socket {
	public:
		Socket(const char *str, int port, int timeout = -1, bool debug = false) : {}
		virtual ~Socket() {
            if (this->_socketdescriptor > 0) {
                close(_socketdescriptor);
                _socketdescriptor = -1;
            }
        };

	protected:
	private:
        int _port;
        struct addrinfo * _address;
        const std::string _name;
        const std::string _hostname;
        std::ostringstream _str;
        int _timeout;
        int _socketdescriptor;
        bool _debug;
};

#endif /* !SOCKET_HPP_ */
