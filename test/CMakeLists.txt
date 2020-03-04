include_directories("include/")
include_directories("../zia/Log/include/")

#####################################
#           Dlsym-Wrapper           #
#####################################
include_directories(../zia/include)
include_directories(../zia/dslym-wrapper/include)

set(
    DLSYM_LIB_SRC
        dlsym-wrapper-tests/dlsym-wrapper-tests-lib.cpp
)

set(
    DLSYM_TEST_SRC
        dlsym-wrapper-tests/dlsym-wrapper-tests-works.cpp
        ../zia/dslym-wrapper/src/DLSymWrapper.cpp
        dlsym-wrapper-tests/dlsym-wrapper-tests-stress.cpp)

add_library(wrapper_test SHARED ${DLSYM_LIB_SRC})
set_target_properties(wrapper_test PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

#####################################
#              Parsing              #
#####################################
include_directories("../zia/iniparser/include/")

set(
        PARSER_TEST_SRC
        parser-tests/parsing-tests.cpp
        ../zia/src/Parser.cpp)

file(COPY parser-tests/example.json DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY parser-tests/example.ini DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(
        Glados
        "../zia/Log/src/Log.cpp"
        "../zia/src/zia.cpp"
        "main.cpp"
        ${DLSYM_TEST_SRC}
        ${PARSER_TEST_SRC}
        "loggerTest.cpp"
)

add_dependencies(Glados wrapper_test cpp-iniparser)

if(WIN32)
    target_link_libraries(Glados CONAN_PKG::gtest cpp-iniparser CONAN_PKG::rapidjson)
else()
    target_link_libraries(Glados CONAN_PKG::gtest dl cpp-iniparser CONAN_PKG::rapidjson)
endif()

if (WIN32)
    add_definitions(-D_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH)
else ()
    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif ()

add_test(NAME Glados
        COMMAND Glados)