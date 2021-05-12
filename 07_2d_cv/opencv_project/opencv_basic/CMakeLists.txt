cmake_minimum_required(VERSION 3.14)
project(opencv_basic)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)

add_executable(01_read_image image_operation/01_read_image.cpp)
target_link_libraries(01_read_image ${OpenCV_LIBS})

add_executable(02_write_image image_operation/02_write_image.cpp)
target_link_libraries(02_write_image ${OpenCV_LIBS})

add_executable(03_image_info image_operation/03_image_info.cpp)
target_link_libraries(03_image_info ${OpenCV_LIBS})

add_executable(04_image_cut image_operation/04_image_cut.cpp)
target_link_libraries(04_image_cut ${OpenCV_LIBS})


add_executable(05_image_mirror image_operation/05_image_mirror.cpp)
target_link_libraries(05_image_mirror ${OpenCV_LIBS})

add_executable(06_image_scale image_operation/06_image_scale.cpp)
target_link_libraries(06_image_scale ${OpenCV_LIBS})


add_executable(07_image_shift image_operation/07_image_shift.cpp)
target_link_libraries(07_image_shift ${OpenCV_LIBS})


add_executable(08_image_rotate image_operation/08_image_rotate.cpp)
target_link_libraries(08_image_rotate ${OpenCV_LIBS})


add_executable(09_image_affine image_operation/09_image_affine.cpp)
target_link_libraries(09_image_affine ${OpenCV_LIBS})

add_executable(10_image_pyramid image_operation/10_image_pyramid.cpp)
target_link_libraries(10_image_pyramid ${OpenCV_LIBS})


add_executable(01_image_fusion image_effects/01_image_fusion.cpp)
target_link_libraries(01_image_fusion ${OpenCV_LIBS})


add_executable(02_image_gray image_effects/02_image_gray.cpp)
target_link_libraries(02_image_gray ${OpenCV_LIBS})


add_executable(03_image_gray_reverse image_effects/03_image_gray_reverse.cpp)
target_link_libraries(03_image_gray_reverse ${OpenCV_LIBS})


add_executable(04_image_color_reverse image_effects/04_image_color_reverse.cpp)
target_link_libraries(04_image_color_reverse ${OpenCV_LIBS})


add_executable(05_image_mosaic image_effects/05_image_mosaic.cpp)
target_link_libraries(05_image_mosaic ${OpenCV_LIBS})


add_executable(06_image_frosted_glass image_effects/06_image_frosted_glass.cpp)
target_link_libraries(06_image_frosted_glass ${OpenCV_LIBS})

add_executable(07_image_relief image_effects/07_image_relief.cpp)
target_link_libraries(07_image_relief ${OpenCV_LIBS})


add_executable(08_image_draw image_effects/08_image_draw.cpp)
target_link_libraries(08_image_draw ${OpenCV_LIBS})


add_executable(09_image_mouse_evt image_effects/09_image_mouse_evt.cpp)
target_link_libraries(09_image_mouse_evt ${OpenCV_LIBS})


add_executable(01_image_brightness image_beautify/01_image_brightness.cpp)
target_link_libraries(01_image_brightness ${OpenCV_LIBS})

add_executable(02_image_hist image_beautify/02_image_hist.cpp)
target_link_libraries(02_image_hist ${OpenCV_LIBS})

add_executable(03_image_equalization image_beautify/03_image_equalization.cpp)
target_link_libraries(03_image_equalization ${OpenCV_LIBS})

add_executable(04_image_color_equalization image_beautify/04_image_color_equalization.cpp)
target_link_libraries(04_image_color_equalization ${OpenCV_LIBS})

