add_subdirectory(dslym-wrapper)

include_directories("include/")

add_executable(
    zia
        "main.cpp"
        "src/zia.cpp"
)
