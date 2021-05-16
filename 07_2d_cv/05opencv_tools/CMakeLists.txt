cmake_minimum_required(VERSION 3.10)
project(05opencv_tools)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)

add_executable(01command_line_parser 01command_line_parser.cpp)
target_link_libraries(01command_line_parser ${OpenCV_LIBS})
