cmake_minimum_required(VERSION 3.16)

project(Proje_OpenCV LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 🔹 OpenCV'nin CMake configlerinin olduğu yer (build klasörü)
set(OpenCV_DIR "C:/opencv/build")

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libs: ${OpenCV_LIBS}")

add_executable(Proje_OpenCV
    src/main.cpp
)

target_include_directories(Proje_OpenCV
    PRIVATE
        ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(Proje_OpenCV
    PRIVATE
        ${OpenCV_LIBS}
)
