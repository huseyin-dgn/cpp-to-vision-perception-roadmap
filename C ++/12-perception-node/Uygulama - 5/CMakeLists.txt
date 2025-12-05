cmake_minimum_required(VERSION 3.10)
project(YoloPerceptionRealtime LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(yolo_perception
    src/main.cpp
    src/frame_types.hpp
    src/detection_types.hpp
    src/yolo_preprocess_node.hpp
    src/yolo_preprocess_node.cpp
    src/yolo_inference_node.hpp
    src/yolo_inference_node.cpp
    src/draw_utils.hpp
    src/draw_utils.cpp
)

target_include_directories(yolo_perception PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(yolo_perception
    "${TORCH_LIBRARIES}"
    ${OpenCV_LIBS}
)

if (MSVC)
    set_property(TARGET yolo_perception PROPERTY VS_DEBUGGER_ENVIRONMENT
        "PATH=%PATH%;${TORCH_INSTALL_PREFIX}/lib")
endif()
