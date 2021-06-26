cmake_minimum_required(VERSION 3.10)
project(test_velodyne_plugin)

set(CMAKE_CXX_STANDARD 11)

# 查找gazebo
find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

add_executable(main main.cpp)
target_link_libraries(main ${GAZEBO_LIBRARIES})
