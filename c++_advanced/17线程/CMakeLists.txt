cmake_minimum_required(VERSION 2.6)
project(17线程)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


add_executable(00thread_simple_use 00thread_simple_use.cpp)


add_executable(01thread_params 01thread_params.cpp)


add_executable(02thread_id 02thread_id.cpp)

