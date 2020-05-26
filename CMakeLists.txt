cmake_minimum_required(VERSION 3.16)
project(laplacian_pyramid)

set(CMAKE_CXX_STANDARD 17)

add_executable(laplacian_pyramid
        src/main.cpp
        src/retouch/Image/ImageLoader.h
        src/retouch/Image/ImageLoader.cpp
        src/retouch/Image/ImageSaver.cpp
        src/retouch/Image/ImageSaver.h
        src/retouch/Image/Image.h
        src/retouch/Image/Image.cpp
        src/retouch/Image/Pixel.h
        src/retouch/Pyramid/GaussianPyramid.h
        src/retouch/Pyramid/GaussianPyramid.cpp src/retouch/Pyramid/LaplacianPyramid.cpp src/retouch/Pyramid/LaplacianPyramid.h src/retouch/LaplacianFiltering/LocalLaplacianFilter.cpp src/retouch/LaplacianFiltering/LocalLaplacianFilter.h src/retouch/LaplacianFiltering/RemapFunction.cpp src/retouch/LaplacianFiltering/RemapFunction.h src/retouch/Others/Hashing.h)

include_directories(vendor/)

target_link_libraries(laplacian_pyramid ${PROJECT_SOURCE_DIR}/vendor/libpng/lib/libpng.so)