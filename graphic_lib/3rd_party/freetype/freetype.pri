#TARGET = qtfreetype

#CONFIG += \
#    static \
#    hide_symbols \
#    exceptions_off rtti_off warn_off \
#    installed

MODULE_INCLUDEPATH += $$PWD/include

#load(qt_helper_lib)

INCLUDEPATH += $$PWD/include

HEADERS += \
    $$PWD/include/ft2build.h \
    $$PWD/include/freetype/config/ftconfig.h \
    $$PWD/include/freetype/config/ftheader.h \
    $$PWD/include/freetype/config/ftmodule.h \
    $$PWD/include/freetype/config/ftoption.h \
    $$PWD/include/freetype/config/ftstdlib.h \
    $$PWD/include/freetype/internal/services/svbdf.h \
    $$PWD/include/freetype/internal/services/svcid.h \
    $$PWD/include/freetype/internal/services/svfntfmt.h \
    $$PWD/include/freetype/internal/services/svgldict.h \
    $$PWD/include/freetype/internal/services/svgxval.h \
    $$PWD/include/freetype/internal/services/svkern.h \
    $$PWD/include/freetype/internal/services/svmm.h \
    $$PWD/include/freetype/internal/services/svotval.h \
    $$PWD/include/freetype/internal/services/svpfr.h \
    $$PWD/include/freetype/internal/services/svpostnm.h \
    $$PWD/include/freetype/internal/services/svprop.h \
    $$PWD/include/freetype/internal/services/svpscmap.h \
    $$PWD/include/freetype/internal/services/svpsinfo.h \
    $$PWD/include/freetype/internal/services/svsfnt.h \
    $$PWD/include/freetype/internal/services/svttcmap.h \
    $$PWD/include/freetype/internal/services/svtteng.h \
    $$PWD/include/freetype/internal/services/svttglyf.h \
    $$PWD/include/freetype/internal/services/svwinfnt.h \
    $$PWD/include/freetype/internal/autohint.h \
    $$PWD/include/freetype/internal/ftcalc.h \
    $$PWD/include/freetype/internal/ftdebug.h \
    $$PWD/include/freetype/internal/ftdriver.h \
    $$PWD/include/freetype/internal/ftgloadr.h \
    $$PWD/include/freetype/internal/ftmemory.h \
    $$PWD/include/freetype/internal/ftobjs.h \
    $$PWD/include/freetype/internal/ftpic.h \
    $$PWD/include/freetype/internal/ftrfork.h \
    $$PWD/include/freetype/internal/ftserv.h \
    $$PWD/include/freetype/internal/ftstream.h \
    $$PWD/include/freetype/internal/fttrace.h \
    $$PWD/include/freetype/internal/ftvalid.h \
    $$PWD/include/freetype/internal/internal.h \
    $$PWD/include/freetype/internal/psaux.h \
    $$PWD/include/freetype/internal/pshints.h \
    $$PWD/include/freetype/internal/sfnt.h \
    $$PWD/include/freetype/internal/t1types.h \
    $$PWD/include/freetype/internal/tttypes.h \
    $$PWD/include/freetype/freetype.h \
    $$PWD/include/freetype/ftadvanc.h \
    $$PWD/include/freetype/ftautoh.h \
    $$PWD/include/freetype/ftbbox.h \
    $$PWD/include/freetype/ftbdf.h \
    $$PWD/include/freetype/ftbitmap.h \
    $$PWD/include/freetype/ftbzip2.h \
    $$PWD/include/freetype/ftcache.h \
    $$PWD/include/freetype/ftcffdrv.h \
    $$PWD/include/freetype/ftchapters.h \
    $$PWD/include/freetype/ftcid.h \
    $$PWD/include/freetype/fterrdef.h \
    $$PWD/include/freetype/fterrors.h \
    $$PWD/include/freetype/ftfntfmt.h \
    $$PWD/include/freetype/ftgasp.h \
    $$PWD/include/freetype/ftglyph.h \
    $$PWD/include/freetype/ftgxval.h \
    $$PWD/include/freetype/ftgzip.h \
    $$PWD/include/freetype/ftimage.h \
    $$PWD/include/freetype/ftincrem.h \
    $$PWD/include/freetype/ftlcdfil.h \
    $$PWD/include/freetype/ftlist.h \
    $$PWD/include/freetype/ftlzw.h \
    $$PWD/include/freetype/ftmac.h \
    $$PWD/include/freetype/ftmm.h \
    $$PWD/include/freetype/ftmodapi.h \
    $$PWD/include/freetype/ftmoderr.h \
    $$PWD/include/freetype/ftotval.h \
    $$PWD/include/freetype/ftoutln.h \
    $$PWD/include/freetype/ftpfr.h \
    $$PWD/include/freetype/ftrender.h \
    $$PWD/include/freetype/ftsizes.h \
    $$PWD/include/freetype/ftsnames.h \
    $$PWD/include/freetype/ftstroke.h \
    $$PWD/include/freetype/ftsynth.h \
    $$PWD/include/freetype/ftsystem.h \
    $$PWD/include/freetype/fttrigon.h \
    $$PWD/include/freetype/ftttdrv.h \
    $$PWD/include/freetype/fttypes.h \
    $$PWD/include/freetype/ftwinfnt.h \
    $$PWD/include/freetype/t1tables.h \
    $$PWD/include/freetype/ttnameid.h \
    $$PWD/include/freetype/tttables.h \
    $$PWD/include/freetype/tttags.h \
    $$PWD/include/freetype/ttunpat.h


SOURCES += \
    $$PWD/src/autofit/afangles.c \
    $$PWD/src/autofit/afdummy.c \
    $$PWD/src/autofit/afglobal.c \
    $$PWD/src/autofit/afhints.c \
    $$PWD/src/autofit/aflatin.c \
    $$PWD/src/autofit/afloader.c \
    $$PWD/src/autofit/afmodule.c \
    $$PWD/src/autofit/autofit.c \
    $$PWD/src/base/ftbase.c \
    $$PWD/src/base/ftbitmap.c \
    $$PWD/src/base/ftbbox.c \
    $$PWD/src/base/ftdebug.c \
    $$PWD/src/base/ftglyph.c \
    $$PWD/src/base/ftfntfmt.c \
    $$PWD/src/base/ftinit.c \
    $$PWD/src/base/ftlcdfil.c \
    $$PWD/src/base/ftmm.c \
    $$PWD/src/base/ftsynth.c \
    $$PWD/src/base/fttype1.c \
    $$PWD/src/bdf/bdf.c \
    $$PWD/src/cache/ftcache.c \
    $$PWD/src/cff/cff.c \
    $$PWD/src/cid/type1cid.c \
    $$PWD/src/gzip/ftgzip.c \
    $$PWD/src/lzw/ftlzw.c \
    $$PWD/src/otvalid/otvalid.c \
    $$PWD/src/otvalid/otvbase.c \
    $$PWD/src/otvalid/otvcommn.c \
    $$PWD/src/otvalid/otvgdef.c \
    $$PWD/src/otvalid/otvgpos.c \
    $$PWD/src/otvalid/otvgsub.c \
    $$PWD/src/otvalid/otvjstf.c \
    $$PWD/src/otvalid/otvmod.c \
    $$PWD/src/pcf/pcf.c \
    $$PWD/src/pfr/pfr.c \
    $$PWD/src/psaux/psaux.c \
    $$PWD/src/pshinter/pshinter.c \
    $$PWD/src/psnames/psmodule.c \
    $$PWD/src/raster/raster.c \
    $$PWD/src/sfnt/sfnt.c \
    $$PWD/src/smooth/smooth.c \
    $$PWD/src/truetype/truetype.c \
    $$PWD/src/type1/type1.c \
    $$PWD/src/type42/type42.c \
    $$PWD/src/winfonts/winfnt.c

win32 {
    SOURCES += $$PWD/src/base/ftsystem.c
} else {
    SOURCES += $$PWD/builds/unix/ftsystem.c
    INCLUDEPATH += $$PWD/builds/unix
}

DEFINES += FT2_BUILD_LIBRARY

#DEFINES += FT_CONFIG_OPTION_SYSTEM_ZLIB
#include(../zlib_dependency.pri)

#DEFINES += FT_CONFIG_OPTION_USE_PNG
#include($$OUT_PWD/../../gui/qtgui-config.pri)
#QMAKE_USE_PRIVATE += libpng

DEFINES += TT_CONFIG_OPTION_SUBPIXEL_HINTING
