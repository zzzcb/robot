cmake_minimum_required(VERSION 3.10)
project(pcl_basic)
set(CMAKE_CXX_STANDARD 14)

# =========================
# 设置输出根目录为build/Debug
set(OUTPUT_DIRECTORY_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})
# 设置可执行程序输出到build/Debug/bin目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY_ROOT}/bin" CACHE PATH "Runtime directory" FORCE)
# 设置库文件输出到build/Debug/lib目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY_ROOT}/lib" CACHE PATH "Library directory" FORCE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY_ROOT}/lib" CACHE PATH "Archive directory" FORCE)
# =========================

set(PCL_DIR ~/3rdparty/pcl-1.9.1/share/pcl-1.9)
find_package(PCL)

## 包含头文件目录
#include_directories(${PCL_INCLUDE_DIRS})
## 设置依赖库链接目录
#link_directories(${PCL_LIBRARY_DIRS})
## 添加预处理器和编译器标记
#add_definitions(${PCL_DEFINITIONS})

#add_executable(01main 01main.cpp)
#target_link_libraries(01main ${PCL_LIBRARIES})
#
#add_executable(02cloud_viewer 02cloud_viewer.cpp)
#target_link_libraries(02cloud_viewer ${PCL_LIBRARIES})

add_executable(03pcl_visualizer 03pcl_visualizer.cpp)
target_link_libraries(03pcl_visualizer ${PCL_LIBRARIES})









