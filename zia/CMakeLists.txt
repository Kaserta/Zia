add_subdirectory(dslym-wrapper)
add_subdirectory("Log")

include_directories("include/")
include_directories("Log/include/")

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_definitions(-DDEBUG)
endif ()

add_executable(
        zia
        "main.cpp"
        "src/zia.cpp"
        src/Parser.cpp include/Parser.hpp)

target_link_libraries(zia libLog CONAN_PKG::rapidjson)