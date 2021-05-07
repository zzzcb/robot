cmake_minimum_required(VERSION 3.14)
project(opencv_basic)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)

add_executable(read_image image_operation/01_read_image.cpp)
target_link_libraries(read_image ${OpenCV_LIBS})

add_executable(write_image image_operation/02_write_image.cpp)
target_link_libraries(write_image ${OpenCV_LIBS})

add_executable(image_info image_operation/03_image_info.cpp)
target_link_libraries(image_info ${OpenCV_LIBS})

add_executable(image_cut image_operation/04_image_cut.cpp)
target_link_libraries(image_cut ${OpenCV_LIBS})


add_executable(image_mirror image_operation/05_image_mirror.cpp)
target_link_libraries(image_mirror ${OpenCV_LIBS})




