cmake_minimum_required(VERSION 3.31)
project(Handmade_Hero)

set(CMAKE_CXX_STANDARD 14)

include_directories(code)
include_directories(code/common)

add_executable(Handmade_Hero
        code/common/typedefs.h
        code/handmade.cpp
        code/handmade.h
        code/win32_handmade.cpp
        code/win32_handmade.h)
