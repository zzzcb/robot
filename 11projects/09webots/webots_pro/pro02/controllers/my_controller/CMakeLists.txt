cmake_minimum_required(VERSION 3.14)
project(my_controller)
set(CMAKE_CXX_STANDARD 11)

# 设置输出目录为 build/release
# set(CMAKE_BUILD_TYPE "release")
# set(OUTPUT_DIRECTORY_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

# 设置输出目录为当前目录
# set(OUTPUT_DIRECTORY_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY_ROOT}" CACHE PATH "Runtime directory" FORCE)


# Setup the project.
# Its name is defined to be the controller directory name.
get_filename_component(PROJECT ${CMAKE_SOURCE_DIR} NAME)


# Get C or C++ sources in the current directory (only).
file(GLOB C_SOURCES *.c)
file(GLOB CPP_SOURCES *.cpp)
set(SOURCES ${C_SOURCES} ${CPP_SOURCES})

# Link with the Webots controller library.
link_directories($ENV{WEBOTS_HOME}/lib/controller)
set (LIBRARIES ${CMAKE_SHARED_LIBRARY_PREFIX}Controller${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_PREFIX}CppController${CMAKE_SHARED_LIBRARY_SUFFIX})
include_directories($ENV{WEBOTS_HOME}/include/controller/c $ENV{WEBOTS_HOME}/include/controller/cpp)
#
## Setup the target executable.
add_executable(${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} ${LIBRARIES})

# Copy the target executable at the right location.
add_custom_command(TARGET ${PROJECT} POST_BUILD COMMAND ${CMAKE_COMMAND} -E
        copy ${CMAKE_BINARY_DIR}/${PROJECT} ${CMAKE_SOURCE_DIR}
)
