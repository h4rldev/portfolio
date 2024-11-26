cmake_minimum_required(VERSION 3.5)
project(backend)

include_directories(backend/include)

find_package(jansson REQUIRED)
find_package(zlib-ng REQUIRED)
find_package(libmicrohttpd REQUIRED)
find_package(libmagic REQUIRED)

target_link_libraries(
  PUBLIC jansson::jansson
  PUBLIC zlib-ng::zlib-ng
  PUBLIC libmicrohttpd::libmicrohttpd
  PUBLIC libmagic::libmagic
)

add_executable(main backend/src/main.c)
