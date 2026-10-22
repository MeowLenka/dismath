cmake_minimum_required(VERSION 3.20)

project(Lab1GrayMultiset LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
endif()

add_library(lab1_core
    src/gray_code.cpp
    src/multiset.cpp
    src/operations.cpp
    src/input.cpp
)

target_include_directories(lab1_core PUBLIC include)

add_executable(lab1 src/main.cpp)
target_link_libraries(lab1 PRIVATE lab1_core)

enable_testing()

#add_executable(lab1_tests tests/test_lab1.cpp)
#target_link_libraries(lab1_tests PRIVATE lab1_core)
#add_test(NAME Lab1Tests COMMAND lab1_tests)

# Запуск:
#cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
#cmake --build build  
#./build/lab1      