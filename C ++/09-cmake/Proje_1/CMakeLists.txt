cmake_minimum_required(VERSION 3.16)

project(Proje1 LANGUAGES CXX)

# C++ standardı
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# src/main.cpp'den bir executable üret
add_executable(Proje1
    src/main.cpp
)
