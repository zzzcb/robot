cmake_minimum_required(VERSION 3.14)
project(qt)

set(CMAKE_CXX_STANDARD 14)
##############################################################################
# Qt Environment
##############################################################################

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets Network)
##############################################################################

include_directories(include)

add_executable(server_main src/server_main.cpp src/Server.cpp)
target_link_libraries(server_main
        Qt5::Core
        Qt5::Widgets
        Qt5::Network
        )


add_executable(client_main src/client_main.cpp src/Client.cpp)
target_link_libraries(client_main
        Qt5::Core
        Qt5::Widgets
        Qt5::Network
        )
