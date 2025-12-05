cmake_minimum_required(VERSION 3.10)
project(Cifar10PerceptionXRay LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# LibTorch yolunu cmake çağırırken vereceksin:
# cmake .. -DCMAKE_PREFIX_PATH="C:/libtorch" gibi
find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(cifar10_app
    src/main.cpp
    src/frame_types.hpp
    src/cifar10_labels.hpp
    src/preprocess_node.hpp
    src/preprocess_node.cpp
    src/classifier_node.hpp
    src/classifier_node.cpp
)

target_include_directories(cifar10_app PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(cifar10_app
    "${TORCH_LIBRARIES}"
    ${OpenCV_LIBS}
)

if (MSVC)
    set_property(TARGET cifar10_app PROPERTY VS_DEBUGGER_ENVIRONMENT
        "PATH=%PATH%;${TORCH_INSTALL_PREFIX}/lib")
endif()
