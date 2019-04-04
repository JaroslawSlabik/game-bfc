QT += network sql

INCLUDEPATH += \
            $${TOP_SOURCE_DIR}/lib_logic_controler

DEPENDPATH += \
            $${TOP_SOURCE_DIR}/lib_logic_controler/database \
            $${TOP_SOURCE_DIR}/lib_logic_controler/logic \
            $${TOP_SOURCE_DIR}/lib_logic_controler/server_logic_communicator

LIBS        += -L$${TOP_SOURCE_DIR}/logic_controler_lib/bin -llogic_controler_lib
