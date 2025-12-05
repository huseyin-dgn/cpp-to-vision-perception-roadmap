cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(libtorch_opencv_test)

# LibTorch yolu
set(CMAKE_PREFIX_PATH "C:/libtorch")

# OpenCV CMake config klasörü (sende burası)
set(OpenCV_DIR "C:/opencv/build/x64/vc16/lib")

# OpenCV ve Torch'u bul
find_package(OpenCV REQUIRED)
find_package(Torch REQUIRED)

# Derlenecek dosya
add_executable(model_test main.cpp)

# OpenCV include klasörleri
include_directories(${OpenCV_INCLUDE_DIRS})

# Kütüphaneleri bağla
target_link_libraries(model_test 
    "${TORCH_LIBRARIES}"
    ${OpenCV_LIBS}
)

# C++ standardı
set_property(TARGET model_test PROPERTY CXX_STANDARD 17)

# LibTorch DLL'lerini exe klasörüne kopyala
add_custom_command(TARGET model_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "C:/libtorch/bin"
    $<TARGET_FILE_DIR:model_test>
)
