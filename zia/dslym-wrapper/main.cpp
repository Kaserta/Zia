//
// Created by azkalaak on 29/01/2020.
//

#include "DLSymWrapper.hpp"

typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} sfColor;

int main(void)
{
    Zia::Library::DLSymWrapper wrap;

    wrap << "/lib64/libcsfml-audio.so";

    std::function<void*(const char *)> ptr;

    wrap.getFunction(ptr, "sfMusic_createFromFile");
    ptr("salut");
    wrap << "/lib64/libcsfml-graphics.so";
    sfColor i = wrap.getVariable<sfColor>("sfWhite");
    return 0;
}