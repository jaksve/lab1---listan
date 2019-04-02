cmake_minimum_required(VERSION 3.13)
project(lablista)
set(CMAKE_CXX_STANDARD 17)
set (SOURCE_FILES main.cpp List.cc)

add_executable(lablista ${SOURCE_FILES})