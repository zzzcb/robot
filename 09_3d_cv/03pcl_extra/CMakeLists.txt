cmake_minimum_required(VERSION 3.10)
project(pcl_advanced)
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

#add_executable(01_iterative_closet_point_icp 01_iterative_closet_point_icp.cpp)
#target_link_libraries(01_iterative_closet_point_icp ${PCL_LIBRARIES})

#add_executable(02_normal_distributions_transform_ndt 02_normal_distributions_transform_ndt.cpp)
#target_link_libraries(02_normal_distributions_transform_ndt ${PCL_LIBRARIES})

#add_executable(03_interactive_icp 03_interactive_icp.cpp)
#target_link_libraries(03_interactive_icp ${PCL_LIBRARIES})

add_executable(04_point_feature_hist_pfh 04_point_feature_hist_pfh.cpp)
target_link_libraries(04_point_feature_hist_pfh ${PCL_LIBRARIES})
