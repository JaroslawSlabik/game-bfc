TEMPLATE = subdirs

SUBDIRS += \
	zlib \
	freetype
	
freetype.dependence = zlib