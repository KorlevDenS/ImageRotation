cmake_minimum_required(VERSION 3.23.2)
project(untitled C)

set(CMAKE_C_STANDARD 23)

add_executable(untitled main.c file_io.c include/file_io.h base_image.c include/base_image.h byte_array.c include/byte_array.h img_manipulations.c include/img_manipulations.h image_rotation.c include/bmp.h bmp.c include/image_rotation.h)
