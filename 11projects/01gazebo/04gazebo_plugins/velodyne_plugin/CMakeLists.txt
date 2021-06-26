cmake_minimum_required(VERSION 3.10)
project(velodyne_plugin)

set(CMAKE_CXX_STANDARD 11)

# 查找gazebo
find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

add_library(velodyne_plugin SHARED plugin.cpp) # 编译动态链接库 最终会生成 libvelodyne_plugin.so
target_link_libraries(velodyne_plugin ${GAZEBO_LIBRARIES})
