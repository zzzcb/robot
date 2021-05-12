cmake_minimum_required(VERSION 3.14)
project(opencv_basic)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)

add_executable(01_inpaint 01_inpaint.cpp)
target_link_libraries(01_inpaint ${OpenCV_LIBS})

add_executable(02_qiebian 02_qiebian.cpp)
target_link_libraries(02_qiebian ${OpenCV_LIBS})

add_executable(03_rotate_qiebian 03_rotate_qiebian.cpp)
target_link_libraries(03_rotate_qiebian ${OpenCV_LIBS})

add_executable(04_detect_line 04_detect_line.cpp)
target_link_libraries(04_detect_line ${OpenCV_LIBS})

add_executable(05_lingjian_count 05_lingjian_count.cpp)
target_link_libraries(05_lingjian_count ${OpenCV_LIBS})

add_executable(06_zhengjainzhao_change_bg 06_zhengjainzhao_change_bg.cpp)
target_link_libraries(06_zhengjainzhao_change_bg ${OpenCV_LIBS})

add_executable(07_road_line_detect 07_road_line_detect.cpp)
target_link_libraries(07_road_line_detect ${OpenCV_LIBS})

