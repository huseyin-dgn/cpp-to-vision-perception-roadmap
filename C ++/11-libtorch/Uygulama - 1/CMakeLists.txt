cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(libtorch_model_test)

# CPU LibTorch kök klasörü
set(CMAKE_PREFIX_PATH "C:/libtorch")
# alternatif garanti yöntem:
# set(Torch_DIR "C:/libtorch/share/cmake/Torch")

find_package(Torch REQUIRED)

add_executable(model_test main.cpp)
target_link_libraries(model_test "${TORCH_LIBRARIES}")

set_property(TARGET model_test PROPERTY CXX_STANDARD 17)
