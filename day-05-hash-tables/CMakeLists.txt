cmake_minimum_required(VERSION 3.20)

project(day_05_hash_tables LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(hash_table_practice examples/hash_table_practice.cpp)
target_include_directories(hash_table_practice PRIVATE include)
target_compile_options(hash_table_practice PRIVATE
    $<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall;-Wextra;-Wpedantic>
)