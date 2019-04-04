QT += core network sql

TEMPLATE = app
TARGET = server_app
DESTDIR = $${TOP_BUILD_DIR}/bin

HEADERS += \
	$$PWD/server.h \
    $$PWD/server_thread.h
	
SOURCES += \
    $$PWD/main.cpp \
    $$PWD/server.cpp \
    $$PWD/server_thread.cpp

include($${TOP_SOURCE_DIR}/logic_controler_lib/logic_controler_lib.pri)

