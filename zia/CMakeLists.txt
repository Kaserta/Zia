include_directories("include/")

add_executable(
    zia
        "main.cpp"
        "src/zia.cpp"
)

add_subdirectory(./NetworkWrapper)
target_link_libraries(zia network-wrapper)