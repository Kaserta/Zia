include_directories(./include)
include_directories(../include)

add_library(
    network-wrapper
        STATIC
        ./src/Socket.cpp
        src/PollWrap.cpp include/PollWrap.hpp)

