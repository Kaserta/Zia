//
// Created by azkalaak on 03/02/2020.
//

#include <gtest/gtest.h>
#include "DLSymWrapper.hpp"

TEST(dlsym_wrapper_tests, normal_tests)
{
    Zia::Library::DLSymWrapper wrap;

#ifdef WIN32
    wrap << "../lib/wrapper_test.dll";
#else
    wrap << "../lib/libwrapper_test.so";
#endif
    ASSERT_EQ(wrap.getVariable<char>("testChar"), 'c');
    ASSERT_EQ(wrap.getVariable<std::string>("testString"), "salut, ceci est un test");
    std::function<int(int)> funcInt;
    wrap.getFunction(funcInt, "testFuncInt");
    ASSERT_EQ(funcInt(1), 1);
    std::function<std::string()> funcString;
    wrap.getFunction(funcString, "testFuncString");
    ASSERT_EQ(funcString(), "hey");
}