cmake_minimum_required(VERSION 3.16)

project(Proje_3 LANGUAGES CXX)

# C++ standardı
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# lib klasöründeki CMakeLists.txt'yi projeye dahil et
add_subdirectory(lib)

# Executable hedef
add_executable(Proje_3
    src/main.cpp
)

# Header dizinlerini hedefe tanıt
target_include_directories(Proje_3
    PRIVATE
        ${CMAKE_SOURCE_DIR}/lib
)

# Kütüphaneyi executable'a linkle
target_link_libraries(Proje_3
    PRIVATE
        my_math_lib
)
