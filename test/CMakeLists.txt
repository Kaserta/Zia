include_directories("include/")
include_directories("../zia/Log/include/")

add_executable(
        Glados
        "../zia/Log/src/Log.cpp"
        "../zia/src/zia.cpp"
        "main.cpp"
        "loggerTest.cpp"
)
target_link_libraries(Glados CONAN_PKG::gtest)

if (WIN32)
    add_definitions(-D_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH)
else ()
    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif ()

add_test(NAME Glados
        COMMAND Glados)