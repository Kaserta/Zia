include_directories("include/")

add_library(
        Log STATIC
        include/Log.h src/Log.cpp
)
