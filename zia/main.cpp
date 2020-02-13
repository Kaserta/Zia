#include <iostream>
#include "NetworkWrapper/include/Socket.hpp"
#include "NetworkWrapper/include/PollWrap.hpp"
#include "UriParser/include/UriParser.hpp"
#if _WIN32
#include <windows.h>
#include <winsock2.h>
#else
#include <unistd.h>
#include <sys/socket.h>
#endif
#include <memory>
#include <fstream>
#define HTDOCS "../../htdocs"
#define PHP "php "

void salut(std::shared_ptr<Zia::Network::Socket> socket, short lebikini)
{
    std::shared_ptr<Zia::Network::Socket> i = socket->accept();
    std::string buffer;
    i->read(buffer, 4096);
    /*std::map<std::string, std::string>*/ std::vector<std::string> parsed_http = UriParser::parse(buffer);
    std::string route = UriParser::split(parsed_http[0], ' ', 1);
    std::cout << route << std::endl;
    if (route[route.size()-1] == '/')
        route += "index.html";
    if (UriParser::split(route, '.', 1) == "php") {
        std::cout << "salut je suis dans le .php" << std::endl;
        std::string to_exec = std::string(PHP) + HTDOCS + route;
        std::system(to_exec.c_str());
    }
    std::ifstream t(HTDOCS+route);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    std::string header = "HTTP/1.1 200 OK\r\n""Content-length: "+std::to_string(str.size())+"\r\n""Content-Type: text/html\r\n""Server: Citédor/0.0.1\r\n""\r\n";
    i->write(header);
    i->write(str);
    i->write("\r\n");
}

int main()
{
    std::shared_ptr<Zia::Network::Socket> p = std::make_shared<Zia::Network::Socket>(Zia::Network::sockType::TCP);
    p->bind(4242);
    p->listen(100);
    Zia::Network::PollWrap u;
    u.addToWatch(p, &salut, POLLIN);
    u.start();
}