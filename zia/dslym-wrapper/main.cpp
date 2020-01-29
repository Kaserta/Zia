//
// Created by azkalaak on 29/01/2020.
//

#include "DLSymWrapper.hpp"

int main(void)
{
    Zia::Library::DLSymWrapper wrap;

    wrap << "/lib64/libsfml-audio.so";

    auto ptr = wrap.getSymbol<int, int>("alGetError");
    return 0;
}