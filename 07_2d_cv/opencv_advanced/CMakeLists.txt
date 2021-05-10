cmake_minimum_required(VERSION 3.14)
project(opencv_advanced)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)

add_executable(01_image_threshold 01_image_threshold.cpp)
target_link_libraries(01_image_threshold ${OpenCV_LIBS})


add_executable(02_image_adaptive_threshold 02_image_adaptive_threshold.cpp)
target_link_libraries(02_image_adaptive_threshold ${OpenCV_LIBS})

add_executable(03_image_threshold_otsu 03_image_threshold_otsu.cpp)
target_link_libraries(03_image_threshold_otsu ${OpenCV_LIBS})

add_executable(04_hsv 04_hsv.cpp)
target_link_libraries(04_hsv ${OpenCV_LIBS})

add_executable(05_hsv_split_by_color 05_hsv_split_by_color.cpp)
target_link_libraries(05_hsv_split_by_color ${OpenCV_LIBS})
