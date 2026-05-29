cmake_minimum_required(VERSION 3.10)
project(lab7)

set(CMAKE_CXX_STANDARD 20)

add_executable(ex1_type_traits ex_7_1_type_traits.cpp
        Vector.h)
add_executable(ex2_traits ex_7_2_Vector_traits.cpp)
add_executable(ex3_policies ex_7_3_Vector_policies.cpp)
add_executable(ex4_operators ex_7_4_Vector_operators.cpp)