cmake_minimum_required(VERSION 3.0.2)
project(hello_pkg)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  nodelet
)

catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES hello_pkg
  CATKIN_DEPENDS nodelet roscpp
#  DEPENDS system_lib
)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(fuck
        src/fuck.cpp
        src/fuck2.cpp)

target_link_libraries(fuck
        ${catkin_LIBRARIES}
        )
if(catkin_EXPORTED_LIBRARIES)
    add_dependencies(fuck ${catkin_EXPORTED_LIBRARIES})
endif()