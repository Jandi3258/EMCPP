cmake_minimum_required(VERSION 3.10)
project(lab8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(Range ex_8_1_Range.cpp)
add_executable(MatrixModifiers ex_8_2_MatrixModifiers.cpp)
add_executable(MatrixIterator ex_8_3_MatrixIterator.cpp)
add_executable(Filter ex_8_4_Filter.cpp)