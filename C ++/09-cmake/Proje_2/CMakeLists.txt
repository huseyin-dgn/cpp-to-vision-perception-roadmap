cmake_minimum_required(VERSION 3.16)

project(Proje_2 LANGUAGES CXX)

# C++ standardı
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Executable target oluştur
add_executable(Proje_2
    src/main.cpp
    src/math_utils.cpp
)

# include/ klasörünü bu target için include path'e ekle
target_include_directories(Proje_2
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)
