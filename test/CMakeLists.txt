include_directories("include/")

add_executable(
    testfoo
        "main.cpp"
)

add_test(NAME testfoo
         COMMAND testfoo)