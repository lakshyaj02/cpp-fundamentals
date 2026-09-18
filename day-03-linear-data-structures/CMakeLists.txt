cmake_minimum_required(VERSION 3.20)

project(day_03_linear_data_structures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(linear_structures examples/linear_structures.cpp)
target_include_directories(linear_structures PRIVATE include)
target_compile_options(linear_structures PRIVATE
    $<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall;-Wextra;-Wpedantic>
)

add_executable(singly_linked_list_test tests/singly_linked_list_test.cpp)
target_include_directories(singly_linked_list_test PRIVATE include)
target_compile_options(singly_linked_list_test PRIVATE
    $<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall;-Wextra;-Wpedantic>
)

add_executable(data_structures_test tests/data_structures_test.cpp)
target_include_directories(data_structures_test PRIVATE include)
target_compile_options(data_structures_test PRIVATE
    $<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall;-Wextra;-Wpedantic>
)

enable_testing()
add_test(NAME singly_linked_list_test COMMAND singly_linked_list_test)
add_test(NAME data_structures_test COMMAND data_structures_test)