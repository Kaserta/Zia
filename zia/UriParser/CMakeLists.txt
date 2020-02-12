include_directories(./include)
include_directories(../include)

add_library(
    uri-parser
        STATIC
        ./src/UriParser.cpp
        ./include/UriParser.hpp)
