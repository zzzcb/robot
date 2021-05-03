# 1 头文件 
include_directories("third_lib/include")

# 2 库文件 
find_library(FUCK fuck HINTS ${PROJECT_SOURCE_DIR}/third_lib/lib) 
    #查找 libfuck.so 并赋值给 FUCK 
find_library(SHIT shit HINTS ${PROJECT_SOURCE_DIR}/third_lib/lib)
    #查找 libshit.so 并赋值给 SHIT 

SET(xxx_LIBRARIES ${FUCK} ${SHIT})  # 外面直接 使用xxx_LIBRARIES 就行了 
