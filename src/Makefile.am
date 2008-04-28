
lib_LTLIBRARIES = libftgl.la

libftgl_la_SOURCES = \
	FTBitmapGlyph.cpp \
	FTCharmap.cpp \
	FTContour.cpp \
	FTExtrdGlyph.cpp \
	FTFace.cpp \
	FTFont.cpp FTFontImpl.h \
	FTGLBitmapFont.cpp FTGLBitmapFontImpl.h \
	FTGLExtrdFont.cpp FTGLExtrdFontImpl.h \
	FTGLOutlineFont.cpp FTGLOutlineFontImpl.h \
	FTGLPixmapFont.cpp FTGLPixmapFontImpl.h \
	FTGLPolygonFont.cpp FTGLPolygonFontImpl.h \
	FTGLTextureFont.cpp FTGLTextureFontImpl.h \
	FTGlyph.cpp \
	FTGlyphContainer.cpp \
	FTGlue.cpp \
	FTLayout.cpp FTLayoutImpl.h \
	FTLibrary.cpp \
	FTOutlineGlyph.cpp \
	FTPixmapGlyph.cpp \
	FTPoint.cpp \
	FTPolyGlyph.cpp \
	FTSimpleLayout.cpp FTSimpleLayoutImpl.h \
	FTSize.cpp \
	FTTextureGlyph.cpp \
	FTVectoriser.cpp \
	$(ftgl_HEADERS)
libftgl_la_CPPFLAGS = -I$(top_srcdir)/include
libftgl_la_CXXFLAGS = $(FT2_CFLAGS) $(GL_CFLAGS)
libftgl_la_LDFLAGS = \
        $(FT2_LIBS) $(GL_LIBS) -no-undefined -version-number @LT_VERSION@

ftgldir = $(includedir)/FTGL
ftgl_HEADERS = \
	../include/FTBBox.h \
	../include/FTBitmapGlyph.h \
	../include/FTCharToGlyphIndexMap.h \
	../include/FTCharmap.h \
	../include/FTContour.h \
	../include/FTExtrdGlyph.h \
	../include/FTFace.h \
	../include/FTFont.h \
	../include/FTGL.h \
	../include/FTGLBitmapFont.h \
	../include/FTGLExtrdFont.h \
	../include/FTGLOutlineFont.h \
	../include/FTGLPixmapFont.h \
	../include/FTGLPolygonFont.h \
	../include/FTGLTextureFont.h \
	../include/FTGlyph.h \
	../include/FTGlyphContainer.h \
	../include/FTLayout.h \
	../include/FTLibrary.h \
	../include/FTList.h \
	../include/FTOutlineGlyph.h \
	../include/FTPixmapGlyph.h \
	../include/FTPoint.h \
	../include/FTPolyGlyph.h \
	../include/FTSimpleLayout.h \
	../include/FTSize.h \
	../include/FTTextureGlyph.h \
	../include/FTVector.h \
	../include/FTVectoriser.h \
	${NULL}

NULL =
