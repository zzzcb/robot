cmake_minimum_required(VERSION 3.14)
project(qt)

set(CMAKE_CXX_STANDARD 14)
##############################################################################
# Qt Environment
##############################################################################

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets)
##############################################################################

include_directories(include)

add_executable(main src/main.cpp src/ZcbWindow.cpp)
target_link_libraries(main
        Qt5::Core
        Qt5::Widgets
        )

