#include <iostream>
#include "NetworkWrapper/include/Socket.hpp"
#include "NetworkWrapper/include/PollWrap.hpp"
#include <sys/socket.h>
#include <memory>
#include <unistd.h>

void salut(std::shared_ptr<Zia::Network::Socket> socket, short lebikini)
{
    std::cout << "salut je suis dans salut: mon short est :" << lebikini <<std::endl;
    std::shared_ptr<Zia::Network::Socket> i = socket->accept();
    std::cout << "le getfd de l'accept de la socket :" << i->getFD() << std::endl;
    std::cout << socket->getFD() << std::endl;

}

int main()
{
    std::cout << "Hello World!" << std::endl;
    std::shared_ptr<Zia::Network::Socket> p = std::make_shared<Zia::Network::Socket>(Zia::Network::sockType::TCP);
    p->bind(4242);
    p->listen(100);
    Zia::Network::PollWrap u;
    u.addToWatch(p, &salut, POLLIN);
    u.start();
}