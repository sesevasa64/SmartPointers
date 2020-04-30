cmake_minimum_required(VERSION 3.15)
project(SmartPointers)

set(CMAKE_CXX_STANDARD 17)

add_executable(SmartPointers main.cpp lib/UniquePtr.h lib/SharedPtr.h)