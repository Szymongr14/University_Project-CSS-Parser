cmake_minimum_required(VERSION 3.25)
project(css_parser_szymon_groszkowski)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(css_parser_szymon_groszkowski
        cssengine.cpp
        cssengine.h
        main.cpp
        mystring.cpp
        mystring.h
        myvector.cpp
        myvector.h)
