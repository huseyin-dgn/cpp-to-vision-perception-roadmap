cmake_minimum_required(VERSION 3.10)
project(PreprocessProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# LibTorch yolunu ortamında ayarlaman gerekiyor:
# cmake .. -DCMAKE_PREFIX_PATH="C:/libtorch"
find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(preprocess_app
    src/main.cpp
    src/frame_types.hpp
    src/preprocess_node.hpp
    src/preprocess_node.cpp
)

target_include_directories(preprocess_app PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(preprocess_app
    "${TORCH_LIBRARIES}"
    ${OpenCV_LIBS}
)

# Windows için: LibTorch DLL'lerini kopyalamak gerekebilir
if (MSVC)
    set_property(TARGET preprocess_app PROPERTY VS_DEBUGGER_ENVIRONMENT
        "PATH=%PATH%;${TORCH_INSTALL_PREFIX}/lib")
endif()
