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
#include <filesystem>
#define HTDOCS "../../htdocs"
#define PHP "php "

void accept_func(std::shared_ptr<Zia::Network::Socket> socket, short lebikini)
{
    std::shared_ptr<Zia::Network::Socket> i = socket->accept();
    std::string buffer;
    i->read(buffer, 4096);
    /*std::map<std::string, std::string>*/ std::vector<std::string> parsed_http = UriParser::parse(buffer);
    std::string route = UriParser::split(parsed_http[0], ' ', 1);
    std::string str;
    std::cout << route << std::endl;
    if (route[route.size()-1] == '/')
        route += "index.html";
    if (UriParser::split(route, '.', 1) == "php") {
        std::system("export REDIRECT_STATUS=200");
        std::system("export SERVER_PROTOCOL='HTTP/1.1'");
        std::system("export DOCUMENT_ROOT='$(pwd)../../htdocs'");
        std::system((std::string("export SCRIPT_NAME=")+route).c_str());
        std::system((std::string("export $_POST'")+parsed_http[parsed_http.size()-1]+"'").c_str());
        std::string to_exec = std::string(PHP) + HTDOCS + route + " > result.txt";
        std::system(to_exec.c_str());
        std::ifstream t("result.txt");
        str = std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        unlink("result.txt");
    }
    else if (std::ifstream(HTDOCS+route)){
        std::ifstream t(HTDOCS+route);
        str = std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    }
    else {
        i->write("HTTP/1.1 404 NOT FOUND\r\nContent-length 0\r\nContent-Type: text/html\r\nServer: Citedor/0.0.1\r\n\r\n404 NOT FOUND\r\n");
        return;
    }
    std::string header = "HTTP/1.1 200 OK\r\nContent-length: "+std::to_string(str.size())+"\r\n""Content-Type: text/html\r\n""Server: Citedor/0.0.1\r\n""\r\n";
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
    u.addToWatch(p, &accept_func, POLLIN);
    u.start();
}