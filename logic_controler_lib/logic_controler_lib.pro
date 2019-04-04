QT +=  core network sql

TARGET = logic_controler_lib
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = $$PWD/bin

include($$PWD/database/database.pri)
include($$PWD/logic/logic.pri)
include($$PWD/server_logic_communicator/server_logic_communicator.pri)
include($$PWD/global_struct/global_struct.pri)
