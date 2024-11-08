cmake_minimum_required(VERSION 3.5)
project(backend)

include_directories(backend/include)

add_executable(main backend/src/main.c)
