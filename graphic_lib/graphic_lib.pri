INCLUDEPATH += $${TOP_SOURCE_DIR}/graphic_lib
DEPENDPATH += $${TOP_SOURCE_DIR}/graphic_lib
include($${TOP_SOURCE_DIR}/graphic_lib/3rd_party/freetype/freetype.pri)
LIBS += -L$${TOP_SOURCE_DIR}/graphic_lib/bin/ -lgraphic_lib