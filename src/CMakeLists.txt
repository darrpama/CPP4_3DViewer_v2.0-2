cmake_minimum_required(VERSION 3.5)

project(3DViewer_2_0 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGL Core Gui OpenGLWidgets)

set(PROJECT_SOURCES
    resources.qrc
    main.cc
    views/screencastthread.h
    views/screencastthread.cc
    views/mainwindow.h
    views/mainwindow.cc
    views/mainwindow.ui
    views/canvas.h
    views/canvas.cc
    controllers/controller.h
    controllers/controller.cc
    models/model.h
    models/model.cc
    models/object.h
    models/object.cc
    models/obj_parser.h
    models/obj_parser.cc
    models/renderer.h
    models/renderer.cc
    models/transform.h
    models/transform.cc
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
    Qt${QT_VERSION_MAJOR}::OpenGL
    Qt6::OpenGLWidgets
)
