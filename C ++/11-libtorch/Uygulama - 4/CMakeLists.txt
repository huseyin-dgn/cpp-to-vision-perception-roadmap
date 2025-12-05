cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(libtorch_opencv_cnn_demo)

# LibTorch
set(CMAKE_PREFIX_PATH "C:/libtorch")

# OpenCV
set(OpenCV_DIR "C:/opencv/build/x64/vc16/lib")

find_package(OpenCV REQUIRED)
find_package(Torch REQUIRED)

add_executable(model_test main.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(model_test
    "${TORCH_LIBRARIES}"
    ${OpenCV_LIBS}
)

set_property(TARGET model_test PROPERTY CXX_STANDARD 17)

add_custom_command(TARGET model_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/libtorch/bin"
        $<TARGET_FILE_DIR:model_test>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/opencv/build/x64/vc16/bin"
        $<TARGET_FILE_DIR:model_test>
)
