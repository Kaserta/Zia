include_directories("include/")

add_executable(
    zia
        "main.cpp"
        "src/zia.cpp"
)

target_link_libraries(zia network-wrapper uri-parser)
add_subdirectory(./NetworkWrapper)
add_subdirectory(./UriParser)