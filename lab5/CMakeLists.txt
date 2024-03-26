cmake_minimum_required(VERSION 3.25)
project(lab5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab5
        boggle.cpp
        EnglishWords.txt
        lexicon.cpp
        lexicon.h)
