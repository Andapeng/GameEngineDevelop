cmake_minimum_required(VERSION 3.16)
project(Editor LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
        Quick
        Quickwidgets
        Qml
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    Editor.ui
    Editor.h
    Editor.cpp
    qml.qrc
)

qt_add_executable(Editor ${PROJECT_SOURCES})
qt_add_qml_module(
    Editor
    URI "Editor"
    VERSION 1.0
    RESOURCE_PREFIX /
    QML_FILES QML/main.qml
    RESOURCES qml.qrc
) 

qt_add_resources(Editor
    "qml"
    PREFIX "/"                              #资源的前缀
    FILES 
        QML/main.qml                       #资源所在的路径
)

set_target_properties(Editor
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(Editor
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Quick
        Qt::QuickWidgets
        Qt::Qml
)
