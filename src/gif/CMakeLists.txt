cmake_minimum_required(VERSION 3.5)

project(GIFLIB VERSION 0.1 LANGUAGES C CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_library(gif_lib
    gif_image/qgifglobal.h
    gif_image/qgifimage_p.h
    gif_image/qgifimage.cpp
    gif_image/qgifimage.h
    gif_lib/dgif_lib.c
    gif_lib/egif_lib.c
    gif_lib/gif_err.c
    gif_lib/gif_font.c
    gif_lib/gif_hash.c
    gif_lib/gif_hash.h
    gif_lib/gif_lib_private.h
    gif_lib/gif_lib.h
    gif_lib/gifalloc.c
    gif_lib/quantize.c
)

target_link_libraries(gif_lib Qt6::Core Qt6::Widgets)
