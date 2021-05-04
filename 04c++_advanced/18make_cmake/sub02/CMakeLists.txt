cmake_minimum_required (VERSION 2.6)

project (sub01)

set(CMAKE_CXX_STANDARD 11)


add_executable(main main.cpp)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/third_lib)
find_package(xxx) # 引入 Findxxx.cmake 
target_link_libraries(main ${xxx_LIBRARIES})


