cmake_minimum_required(VERSION 3.5)

project(3DViewer2 VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/3DViewer2    
    ${CMAKE_SOURCE_DIR}/model
    ${CMAKE_SOURCE_DIR}/gif_recorder/3rdParty/giflib
    ${CMAKE_SOURCE_DIR}/gif_recorder/gifimage
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)

set(PROJECT_SOURCES
        ${CMAKE_SOURCE_DIR}/3DViewer2/main.cc
        ${CMAKE_SOURCE_DIR}/3DViewer2/mainwindow.cc
        ${CMAKE_SOURCE_DIR}/3DViewer2/mainwindow.h
        ${CMAKE_SOURCE_DIR}/3DViewer2/mainwindow.ui
        ${CMAKE_SOURCE_DIR}/3DViewer2/model_renderer.cc
        ${CMAKE_SOURCE_DIR}/3DViewer2/model_renderer.h
        ${CMAKE_SOURCE_DIR}/3DViewer2/controller.cc
        ${CMAKE_SOURCE_DIR}/3DViewer2/controller.h
        ${CMAKE_SOURCE_DIR}/3DViewer2/settings.h
        ${CMAKE_SOURCE_DIR}/3DViewer2/settings_type.h
        ${CMAKE_SOURCE_DIR}/3DViewer2/record.h
        ${CMAKE_SOURCE_DIR}/3DViewer2/record.cc

        ${CMAKE_SOURCE_DIR}/gif_recorder/gifimage/qgifglobal.h
        ${CMAKE_SOURCE_DIR}/gif_recorder/gifimage/qgifimage.h
        ${CMAKE_SOURCE_DIR}/gif_recorder/gifimage/qgifimage_p.h

        ${CMAKE_SOURCE_DIR}/gif_recorder/3rdParty/giflib/dgif_lib.c
        ${CMAKE_SOURCE_DIR}/gif_recorder/3rdParty/giflib/egif_lib.c
        ${CMAKE_SOURCE_DIR}/gif_recorder/3rdParty/giflib/gif_err.c
        ${CMAKE_SOURCE_DIR}/gif_recorder/3rdParty/giflib/gif_hash.c
        ${CMAKE_SOURCE_DIR}/gif_recorder/3rdParty/giflib/gifalloc.c
        ${CMAKE_SOURCE_DIR}/gif_recorder/3rdParty/giflib/quantize.c

        ${CMAKE_SOURCE_DIR}/gif_recorder/gifimage/qgifimage.cpp
)

add_library(ModelLib SHARED
        ${CMAKE_SOURCE_DIR}/model/affine_command.h
        ${CMAKE_SOURCE_DIR}/model/affine_invoker.h
        ${CMAKE_SOURCE_DIR}/model/data_object.h
        ${CMAKE_SOURCE_DIR}/model/exceptions.h
        ${CMAKE_SOURCE_DIR}/model/i_model.h
        ${CMAKE_SOURCE_DIR}/model/i_parser.h
        ${CMAKE_SOURCE_DIR}/model/min_max_values.h
        ${CMAKE_SOURCE_DIR}/model/model.cc
        ${CMAKE_SOURCE_DIR}/model/model.h
        ${CMAKE_SOURCE_DIR}/model/object_info.h
        ${CMAKE_SOURCE_DIR}/model/parser_factory.h
        ${CMAKE_SOURCE_DIR}/model/parser.h
        ${CMAKE_SOURCE_DIR}/model/type_command.h
        ${CMAKE_SOURCE_DIR}/model/type_data_object.h
        ${CMAKE_SOURCE_DIR}/model/exceptions.h

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3DViewer2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3DViewer2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3DViewer2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(3DViewer2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL Qt${QT_VERSION_MAJOR}::OpenGLWidgets ModelLib)

set_target_properties(3DViewer2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer2)
endif()
