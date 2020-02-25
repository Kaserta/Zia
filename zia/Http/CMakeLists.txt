include_directories(./include)
include_directories(../include)

add_library(
    http-status
    STATIC
    ./src/HttpResponse.cpp
    ./src/HttpRequest.cpp
    ./include/HttpResponse.hpp
    ./include/HttpRequest.cpp)
