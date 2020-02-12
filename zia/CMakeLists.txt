include_directories("include/")

add_executable(
    zia
        "main.cpp"
        "src/zia.cpp"
)

target_link_libraries(zia network-wrapper)
add_subdirectory(./NetworkWrapper)
