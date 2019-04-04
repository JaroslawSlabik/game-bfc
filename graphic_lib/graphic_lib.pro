
QT += core gui widgets

TARGET = graphic_lib
TEMPLATE = lib
CONFIG += staticlib c++11 console

DESTDIR = $$PWD/bin

include($$PWD/3rd_party/freetype/freetype.pri)

SOURCES += \
    boxmesh.cpp \
    i_mesh.cpp \
    opengl_object.cpp \
    i_texture.cpp \
    texture.cpp \
    shader.cpp \
    opengl_object_2d.cpp \
    opengl_object_3d.cpp \
    plate_mesh.cpp \
    opengl_text_render_2d.cpp
	
HEADERS += \
    i_mesh.h \
    boxmesh.h \
    opengl_object.h \
    i_texture.h \
    texture.h \
    shader.h \
    opengl_object_2d.h \
    opengl_object_3d.h \
    plate_mesh.h \
    opengl_text_render_2d.h

