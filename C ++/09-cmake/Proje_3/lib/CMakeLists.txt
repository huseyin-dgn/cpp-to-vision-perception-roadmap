# my_math.cpp'ten bir kütüphane oluştur
add_library(my_math_lib
    my_math.cpp
)

# Bu kütüphaneyi kullananlar, bu klasördeki header'ları görebilsin
target_include_directories(my_math_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)