include_directories("include/")

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_definitions(-DDEBUG)
endif ()

add_library(
        libLog STATIC
        include/Log.hpp src/Log.cpp
)
