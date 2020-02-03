include_directories("include/")

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


add_executable(
    Glados
        "../zia/src/zia.cpp"
        "main.cpp"
        ${DLSYM_TEST_SRC}
)
add_dependencies(Glados wrapper_test)

if(WIN32)
target_link_libraries(Glados CONAN_PKG::gtest)
else()
target_link_libraries(Glados CONAN_PKG::gtest dl)
endif()

SET(CMAKE_CXX_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")

add_test(NAME Glados
        COMMAND Glados)