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


add_executable(06_contours 06_contours.cpp)
target_link_libraries(06_contours ${OpenCV_LIBS})


add_executable(01_filter_mean image_conv/01_filter_mean.cpp)
target_link_libraries(01_filter_mean ${OpenCV_LIBS})

add_executable(02_filter_median image_conv/02_filter_median.cpp)
target_link_libraries(02_filter_median ${OpenCV_LIBS})

add_executable(03_filter_gaussian image_conv/03_filter_gaussian.cpp)
target_link_libraries(03_filter_gaussian ${OpenCV_LIBS})


add_executable(04_sobel image_conv/04_sobel.cpp)
target_link_libraries(04_sobel ${OpenCV_LIBS})

add_executable(05_scharr image_conv/05_scharr.cpp)
target_link_libraries(05_scharr ${OpenCV_LIBS})

add_executable(06_laplacian image_conv/06_laplacian.cpp)
target_link_libraries(06_laplacian ${OpenCV_LIBS})

add_executable(07_image_sharp image_conv/07_image_sharp.cpp)
target_link_libraries(07_image_sharp ${OpenCV_LIBS})

add_executable(08_canny image_conv/08_canny.cpp)
target_link_libraries(08_canny ${OpenCV_LIBS})

add_executable(09_bilateral_filter image_conv/09_bilateral_filter.cpp)
target_link_libraries(09_bilateral_filter ${OpenCV_LIBS})

add_executable(07_face_detect 07_face_detect.cpp)
target_link_libraries(07_face_detect ${OpenCV_LIBS})


add_executable(08_video_process 08_video_process.cpp)
target_link_libraries(08_video_process ${OpenCV_LIBS})

