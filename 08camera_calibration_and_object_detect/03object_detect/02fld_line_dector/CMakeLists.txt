cmake_minimum_required(VERSION 3.14)
project(opencv_basic)

set(CMAKE_CXX_STANDARD 14)

#============================================
# 设置输出目录为 build/bin build/lib
set(OUTPUT_DIRECTORY_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY_ROOT}/bin" CACHE PATH "Runtime directory" FORCE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY_ROOT}/lib" CACHE PATH "Library directory" FORCE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY_ROOT}/lib" CACHE PATH "Archive directory" FORCE)
#============================================

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ~/3rdparty/OpenCV-3.4/share/OpenCV)
find_package(OpenCV)

add_executable(01fld_line_dector 01fld_line_dector.cpp)
target_link_libraries(01fld_line_dector ${OpenCV_LIBS})


