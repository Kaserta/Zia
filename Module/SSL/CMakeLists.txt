set (MODULE_NAME ssl_module)

add_definitions("-fpic -shared -W -Wall -Wextra -ldl -lssl -lcrypto")
set(SRC SSLModule.cpp SSLModule.hpp)
add_library(${MODULE_NAME} SHARED ${SRC})
target_link_libraries(${MODULE_NAME} ssl crypto)