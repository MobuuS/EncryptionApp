cmake_minimum_required(VERSION 3.31)
project(EncryptionApp)

set(CMAKE_CXX_STANDARD 26)

add_executable(EncryptionApp main.cpp
        App.cpp
        App.h)
