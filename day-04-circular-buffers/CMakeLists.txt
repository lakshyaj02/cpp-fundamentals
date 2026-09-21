cmake_minimum_required(VERSION 3.20)

project(day_04_circular_buffers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(circular_buffer_practice examples/circular_buffer_practice.cpp)
target_include_directories(circular_buffer_practice PRIVATE include)
target_compile_options(circular_buffer_practice PRIVATE
    $<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall;-Wextra;-Wpedantic>
)