#include <iostream>
#include "Log.hpp"
#include <thread>

int main()
{
    std::cout << "I'm a program !" << std::endl;
    WARNLOG("I'm a warning bruh.");
    std::this_thread::sleep_for(std::chrono::seconds(5));
    INFOSLOG("I'm an infos 5 sec after the warning.");
    std::this_thread::sleep_for(std::chrono::seconds(5));
    ERRLOG("And I'm the final error 5 sec after the infos.");
}
