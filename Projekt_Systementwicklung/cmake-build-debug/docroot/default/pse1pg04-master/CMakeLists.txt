cmake_minimum_required(VERSION 3.15)
project(pse1pg04 C)

set(CMAKE_C_STANDARD 11)

add_executable(pse1pg04 echo_server.c httplib.h httplib.c request.c request.h response.c response.h)