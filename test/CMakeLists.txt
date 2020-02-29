include_directories("include/")

add_executable(
    Glados
        "../zia/src/zia.cpp"
        "main.cpp"
)
target_link_libraries(Glados CONAN_PKG::gtest)

SET(CMAKE_CXX_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")

add_test(NAME Glados
         COMMAND Glados)