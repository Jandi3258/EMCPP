cmake_minimum_required(VERSION 4.1)
project(Cwiczenia5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Cwiczenia5
        ex1_Pair.cpp
        ex2_staticVector.cpp
        ex3_dynamicVector.cpp
        ex4_conversion.cpp
        staticVector.h
        dynamicVector.h)
