//
// Created by azkalaak on 03/02/2020.
//

#include <gtest/gtest.h>
#include "DLSymWrapper.hpp"

//---------- WARNING! this test is a stress test, DO NOT REPRODUCE AT HOME! -----------
TEST(dlsym_wrapper_tests, stress_tests)
{
    Zia::Library::DLSymWrapper wrap;

    ASSERT_ANY_THROW(wrap << ":D I'm failing");
#ifdef _WIN32
    wrap << "./wrapper_test.dll";
#else
    wrap << "../lib/libwrapper_test.so";
#endif
    ASSERT_ANY_THROW(wrap << ":D I'm another fail!");
    ASSERT_ANY_THROW(wrap.getVariable<char>("testChar"));
#ifdef _WIN32
    wrap << "./wrapper_test.dll";
#else
    wrap << "../lib/libwrapper_test.so";
#endif
    ASSERT_ANY_THROW(wrap.getVariable<int>("12"));
    ASSERT_ANY_THROW(wrap.getVariable<std::string>("testInt"));
    std::function<int(int)> func;
    ASSERT_ANY_THROW(wrap.getFunction(func, "testInt"));
}