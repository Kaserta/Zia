include_directories(include/)

add_library(dlsym-wrapper SHARED src/DLSymWrapper.cpp)

add_executable(
    dlsym-wrapper-test
        src/DLSymWrapper.cpp
        main.cpp)

if(WIN32)
else()
    target_link_libraries(dlsym-wrapper-test dl)
endif()