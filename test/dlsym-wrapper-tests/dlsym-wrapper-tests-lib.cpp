//
// Created by azkalaak on 03/02/2020.
//
#include <string>

#ifdef _WIN32
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT extern "C"
#endif

EXPORT const char testChar = 'c';

EXPORT const std::string testString = "salut, ceci est un test";

EXPORT int testFuncInt(int returnWanted)
{
    return returnWanted;
}

EXPORT std::string testFuncString()
{
    return "hey";
}