cmake_minimum_required(VERSION 3.5)
project(zia)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(zia)
add_subdirectory(test)
