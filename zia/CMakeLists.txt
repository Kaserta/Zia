add_subdirectory(dslym-wrapper)
add_subdirectory(iniparser)
add_subdirectory("Log")

include_directories("include/")
include_directories("Log/include/")
include_directories("iniparser/include/")

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_definitions(-DDEBUG)
endif ()

add_executable(
        zia
        "main.cpp"
        "src/zia.cpp"
        src/Parser.cpp include/Parser.hpp)

add_dependencies(zia libLog cpp-iniparser)
target_link_libraries(zia libLog cpp-iniparser CONAN_PKG::rapidjson)