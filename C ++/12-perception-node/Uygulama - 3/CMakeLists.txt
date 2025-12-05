cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(yolov8_libtorch_inference)

# LibTorch kurulu yol
set(CMAKE_PREFIX_PATH "C:/libtorch")

# OpenCV kurulu yol
# Eğer daha önce bu ayarla sorunsuz çalıştıysan aynen bırak
set(OpenCV_DIR "C:/opencv/build/x64/vc16/lib")

find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)

# Çıkacak exe adı -> yolov8_app
add_executable(yolov8_app main.cpp)

# OpenCV include
include_directories(${OpenCV_INCLUDE_DIRS})

# Bağlanacak kütüphaneler
target_link_libraries(yolov8_app
    "${TORCH_LIBRARIES}"
    ${OpenCV_LIBS}
)

set_property(TARGET yolov8_app PROPERTY CXX_STANDARD 17)

# LibTorch ve OpenCV DLL'lerini exe yanına kopyala
add_custom_command(TARGET yolov8_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/libtorch/bin"
        $<TARGET_FILE_DIR:yolov8_app>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/opencv/build/x64/vc16/bin"
        $<TARGET_FILE_DIR:yolov8_app>
)
