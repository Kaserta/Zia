cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(./include)
add_library(cpp-iniparser STATIC ./src/INIConfig.cpp ./src/INIParser.cpp ./src/Utilities.cpp )