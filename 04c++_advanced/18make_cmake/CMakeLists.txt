# 表示cmake的最低版本
cmake_minimum_required (VERSION 2.6)

# 表示目前编译的项目
project (18make_cmake)

# 表示当前编译使用c++11版本来编译程序
set(CMAKE_CXX_STANDARD 11)


# 生成可执行程序  
add_executable(00test 00test.cpp)

# 子工程的创建
add_subdirectory(sub01)

# 设置变量 
set(zcb tom)

# 输出变量 
message("zcb is ${zcb}")



# 导入三方库 
# 1 头文件 
include_directories("third_lib/include")

# 2 库文件 
add_executable(tom tom.cpp) # tom.cpp 中用到了 third_lib
target_link_libraries( 
    tom 
    ${PROJECT_SOURCE_DIR}/third_lib/lib/libfuck.so
    ${PROJECT_SOURCE_DIR}/third_lib/lib/libshit.so
    )


# sub02 文件夹 用于演示 find_package 的使用 
# find_package 的使用 
# 一般别人的项目已经将 配置三方库的 cmake 写好了,一般是Findxxx.cmake 文件名
# 我们需要 
# 1. set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} path) # path 是 Findxxx.cmake 的路径 
# 2. find_package(xxx)
# 3. target_link_libraries(YYY) # YYY 一般是xxx_LIBRARIES,如果猜不对，自己去Findxxx.cmake 中看，是如何set的

