//
// Created by azkalaak on 29/01/2020.
//

#include "DLSymWrapper.hpp"

int main(void)
{
    Zia::Library::DLSymWrapper wrap;

    wrap << "../lib/libdlsym-wrapper.so";
    char i = wrap.getVariable<char>("test");
    std::cout << i << std::endl;
    return 0;
}