cmake_minimum_required(VERSION 3.20)

project(day_01_memory_fundamentals LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(add_study_example target source)
    add_executable(${target} ${source})
    target_compile_options(${target} PRIVATE
        $<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall;-Wextra;-Wpedantic>
    )
endfunction()

add_study_example(stack_heap examples/01_stack_heap.cpp)
add_study_example(pointers_references examples/02_pointers_references.cpp)
add_study_example(pointer_arithmetic examples/03_pointer_arithmetic.cpp)
add_study_example(lifetime examples/04_lifetime.cpp)
add_study_example(allocation examples/05_allocation.cpp)
add_study_example(copy_semantics examples/06_copy_semantics.cpp)
add_study_example(layout examples/07_layout.cpp)

option(ENABLE_UNSAFE_LABS "Build intentionally invalid examples for sanitizer study" OFF)

if(ENABLE_UNSAFE_LABS)
    add_study_example(unsafe_memory unsafe/unsafe_memory.cpp)
    target_compile_options(unsafe_memory PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(unsafe_memory PRIVATE -fsanitize=address,undefined)
endif()