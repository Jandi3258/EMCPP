cmake_minimum_required(VERSION 4.1)
project(CopyMoveWlasnaImplementacja)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CopyMoveWlasnaImplementacja
        matrix_test.cpp
        matrix_test.h
        copy.h
        move.h
        inheritance.h)
