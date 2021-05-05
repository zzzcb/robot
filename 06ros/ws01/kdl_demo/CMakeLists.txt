cmake_minimum_required(VERSION 3.17)
project(kdl_demo)

set(CMAKE_CXX_STANDARD 14)

find_package(orocos_kdl)
include_directories(${orocos_kdl_INCLUDE_DIRS})

add_executable(demo demo.cpp)
add_executable(ur5_fk ur5_fk.cpp)
add_executable(ur5_ik_nr ur5_ik_nr.cpp)
add_executable(ur5_ik_nr_jl ur5_ik_nr_jl.cpp)
add_executable(ur5_ik_lma ur5_ik_lma.cpp)

target_link_libraries(
        demo
        ${orocos_kdl_LIBRARIES}
)
target_link_libraries(
        ur5_fk
        ${orocos_kdl_LIBRARIES}
)
target_link_libraries(
        ur5_ik_nr
        ${orocos_kdl_LIBRARIES}
)
target_link_libraries(
        ur5_ik_nr_jl
        ${orocos_kdl_LIBRARIES}
)
target_link_libraries(
        ur5_ik_lma
        ${orocos_kdl_LIBRARIES}
)
