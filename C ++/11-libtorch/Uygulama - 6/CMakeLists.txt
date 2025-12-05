cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(cifar10_libtorch_inference)

# LibTorch kurulu yol
set(CMAKE_PREFIX_PATH "C:/libtorch")

# OpenCV kurulu yol
set(OpenCV_DIR "C:/opencv/build/x64/vc16/lib")

find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(model_test main.cpp)

# OpenCV include
include_directories(${OpenCV_INCLUDE_DIRS})

# Bağlanacak kütüphaneler
target_link_libraries(model_test
    "${TORCH_LIBRARIES}"
    ${OpenCV_LIBS}
)

set_property(TARGET model_test PROPERTY CXX_STANDARD 17)

# LibTorch ve OpenCV DLL'lerini exe yanına kopyala
add_custom_command(TARGET model_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/libtorch/bin"
        $<TARGET_FILE_DIR:model_test>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/opencv/build/x64/vc16/bin"
        $<TARGET_FILE_DIR:model_test>
)
