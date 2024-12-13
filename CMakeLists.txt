cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 26)

add_executable(untitled main.cpp
        Word_pair.cpp
        Word_pair.h
        Vocabulary.cpp
        Vocabulary.h)
