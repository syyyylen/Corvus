cmake_minimum_required(VERSION 3.28)
project(Corvus)

set(CMAKE_CXX_STANDARD 17)

add_executable(Corvus main.cpp
        Core/Window.cpp
        Core/Window.h
        Core/CorvusEditor.cpp
        Core/CorvusEditor.h)
