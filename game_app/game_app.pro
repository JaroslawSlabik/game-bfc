QT += core gui widgets

TEMPLATE = app
TARGET = game_app
DESTDIR = $${TOP_BUILD_DIR}/bin
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11 console
CONFIG -= app_bundle

#HEADERS += \
#    main_window.h

SOURCES += \
    main.cpp #\
#    main_window.cpp

include($${TOP_SOURCE_DIR}/graphic_lib/graphic_lib.pri)
include(gui_frame/gui_frame.pri)
include(gui_items/gui_items.pri)
include($${TOP_SOURCE_DIR}/logic_controler_lib/logic_controler_lib.pri)
