cmake_minimum_required(VERSION 3.20)

project(day_02_raii_modern_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(add_study_example target source)
    add_executable(${target} ${source})
    target_compile_options(${target} PRIVATE
        $<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall;-Wextra;-Wpedantic>
    )
endfunction()

add_study_example(special_members examples/01_special_members.cpp)
add_study_example(raii examples/02_raii.cpp)
add_study_example(rule_of_three examples/03_rule_of_three.cpp)
add_study_example(rule_of_five examples/04_rule_of_five.cpp)
add_study_example(rule_of_zero examples/05_rule_of_zero.cpp)
add_study_example(unique_ownership examples/06_unique_ptr.cpp)
add_study_example(shared_ownership examples/07_shared_weak_ptr.cpp)