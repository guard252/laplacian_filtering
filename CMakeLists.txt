cmake_minimum_required(VERSION 3.16)
project(laplacian_pyramid)

set(CMAKE_CXX_STANDARD 17)

add_executable(laplacian_pyramid src/main.cpp)

include_directories(vendor/)

target_link_libraries(laplacian_pyramid ${PROJECT_SOURCE_DIR}/vendor/libpng/lib/libpng.a)