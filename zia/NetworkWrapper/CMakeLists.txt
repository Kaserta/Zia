include_directories(./include)
include_directories(../include)

add_library(
    network-wrapper
        SHARED
        ./src/Socket.cpp
)