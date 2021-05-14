cmake_minimum_required(VERSION 3.14)
project(01calibration)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)

add_executable(01_calibration_chessboard 01_calibration_chessboard.cpp)
target_link_libraries(01_calibration_chessboard ${OpenCV_LIBS})


add_executable(02_calibration_chessboard_video 02_calibration_chessboard_video.cpp)
target_link_libraries(02_calibration_chessboard_video ${OpenCV_LIBS})

add_executable(03_calibration_circleboard_video 03_calibration_circleboard_video.cpp)
target_link_libraries(03_calibration_circleboard_video ${OpenCV_LIBS})

add_executable(04_calibration_a_circleboard_video 04_calibration_a_circleboard_video.cpp)
target_link_libraries(04_calibration_a_circleboard_video ${OpenCV_LIBS})


add_executable(05_undistort 05_undistort.cpp)
target_link_libraries(05_undistort ${OpenCV_LIBS})

add_executable(06_undistort 06_undistort.cpp)
target_link_libraries(06_undistort ${OpenCV_LIBS})



