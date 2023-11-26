cmake_minimum_required(VERSION 3.5)

project(3DViewer_2_0 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGL Core Gui OpenGLWidgets)

set(PROJECT_SOURCES
    resources.qrc
    main.cc
    views/mainwindow.h
    views/mainwindow.cc
    views/mainwindow.ui
    views/canvas.h
    views/canvas.cc
    controllers/controller_singleton.h
    controllers/controller_singleton.cc
    models/model_facade.h
    models/model_facade.cc
    models/object.h
    models/object.cc
    models/obj_parser.h
    models/obj_parser.cc
    models/renderer.h
    models/renderer.cc
    models/transform.h
    models/transform.cc
    models/settings.h
    models/settings.cc
    models/screenshot_strategy.h
    models/screenshot_strategy.cc
    models/matrix4x4.h
    models/matrix4x4.cc
)


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::OpenGL
    Qt6::OpenGLWidgets
)
