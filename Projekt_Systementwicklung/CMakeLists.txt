cmake_minimum_required(VERSION 3.10)
project(PSE C)

set(CMAKE_C_STANDARD 11)

set(CRYPTO_LIBRARY libcrypto.a)

add_executable(PSE echo_server.c httplib.c httplib.h base64.c base64.h error_handeling.c error_handeling.h authentication_handeling.c authentication_handeling.h file_handeling.c file_handeling.h request_handeling.c request_handeling.h)
target_link_libraries(PSE ${CMAKE_C_FLAGS} ${CRYPTO_LIBRARY})