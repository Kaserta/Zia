cmake_minimum_required(VERSION 2.8)
project(salut)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(SRC main.cpp Storage.hpp)

add_executable(zia_dummy, ${SRC})
