include_directories(include/)

add_library(dlsym-wrapper src/DLSymWrapper.cpp)

add_executable(
    dlsym-wrapper-test
        src/DLSymWrapper.cpp
        main.cpp)

target_link_libraries(dlsym-wrapper-test dl)