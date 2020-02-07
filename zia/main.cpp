#include <iostream>
#include "Log.hpp"

int main()
{
    std::cout << "I'm a program !" << std::endl;
    WARNLOG("I'm a warning bruh.");
    Sleep(5000);
    INFOSLOG("I'm an infos 5 sec after the warning.");
    Sleep(5000);
    ERRLOG("And I'm the final error 5 sec after the infos.");
}