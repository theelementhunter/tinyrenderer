cmake_minimum_required(VERSION 3.20)
project(TinyRenderer)

set(CMAKE_CXX_STANDARD 14)

# Tell CMake to create an executable named "TinyRenderer"
# using main.cpp AND tgaimage.cpp
add_executable(TinyRenderer main.cpp tgaimage.cpp)