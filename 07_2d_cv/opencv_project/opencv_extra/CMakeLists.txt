cmake_minimum_required(VERSION 3.14)
project(opencv_extra)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)

add_executable(01_image_dilate 01_image_dilate.cpp)
target_link_libraries(01_image_dilate ${OpenCV_LIBS})

add_executable(02_image_erode 02_image_erode.cpp)
target_link_libraries(02_image_erode ${OpenCV_LIBS})

add_executable(03_image_opening 03_image_opening.cpp)
target_link_libraries(03_image_opening ${OpenCV_LIBS})

add_executable(04_image_closing 04_image_closing.cpp)
target_link_libraries(04_image_closing ${OpenCV_LIBS})

add_executable(05_image_yanzhengma 05_image_yanzhengma.cpp)
target_link_libraries(05_image_yanzhengma ${OpenCV_LIBS})

add_executable(06_hough_line 06_hough_line.cpp)
target_link_libraries(06_hough_line ${OpenCV_LIBS})

add_executable(07_hough_circle 07_hough_circle.cpp)
target_link_libraries(07_hough_circle ${OpenCV_LIBS})


add_executable(08_perspective 08_perspective.cpp)
target_link_libraries(08_perspective ${OpenCV_LIBS})

add_executable(09_perspective2 09_perspective2.cpp)
target_link_libraries(09_perspective2 ${OpenCV_LIBS})

add_executable(10_template_match 10_template_match.cpp)
target_link_libraries(10_template_match ${OpenCV_LIBS})

add_executable(11_flood_fill 11_flood_fill.cpp)
target_link_libraries(11_flood_fill ${OpenCV_LIBS})

add_executable(12_water_shed 12_water_shed.cpp)
target_link_libraries(12_water_shed ${OpenCV_LIBS})

add_executable(13_background_subtraction 13_background_subtraction.cpp)
target_link_libraries(13_background_subtraction ${OpenCV_LIBS})

add_executable(14_distance_transform 14_distance_transform.cpp)
target_link_libraries(14_distance_transform ${OpenCV_LIBS})
