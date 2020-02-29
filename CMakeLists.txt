cmake_minimum_required(VERSION 3.5)
project(zia)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

if (${UNIX})
	add_definitions("-fPIC -k8 -g3")
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

if(${WIN32})
    add_definitions(/D _CRT_SECURE_NO_WARNINGS)
    add_definitions(/D NOMINMAX)
    add_definitions(/D WIN32_LEAN_AND_MEAN)
    set(GUI_TYPE WIN32)
endif(${WIN32})


find_library(dl REQUIRED)

add_subdirectory(zia)
add_subdirectory(test)
add_subdirectory(Module)