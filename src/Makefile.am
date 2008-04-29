
lib_LTLIBRARIES = libftgl.la

libftgl_la_SOURCES = \
	FTBBox.h \
	FTBitmapGlyph.cpp FTBitmapGlyph.h \
	FTCharmap.cpp FTCharmap.h \
	FTCharToGlyphIndexMap.h \
	FTContour.cpp FTContour.h \
	FTExtrdGlyph.cpp FTExtrdGlyph.h \
	FTFace.cpp FTFace.h \
	FTFont.cpp FTFontImpl.h \
	FTFontGlue.cpp \
	FTGLBitmapFont.cpp FTGLBitmapFontImpl.h \
	FTGLExtrdFont.cpp FTGLExtrdFontImpl.h \
	FTGLOutlineFont.cpp FTGLOutlineFontImpl.h \
	FTGLPixmapFont.cpp FTGLPixmapFontImpl.h \
	FTGLPolygonFont.cpp FTGLPolygonFontImpl.h \
	FTGLTextureFont.cpp FTGLTextureFontImpl.h \
	FTGlyph.cpp FTGlyph.h \
	FTGlyphContainer.cpp FTGlyphContainer.h \
	FTGlyphGlue.cpp \
	FTLayout.cpp FTLayoutImpl.h \
	FTLayoutGlue.cpp \
	FTLibrary.cpp FTLibrary.h \
	FTList.h \
	FTOutlineGlyph.cpp FTOutlineGlyph.h \
	FTPixmapGlyph.cpp FTPixmapGlyph.h \
	FTPoint.cpp FTPoint.h \
	FTPolyGlyph.cpp FTPolyGlyph.h \
	FTSimpleLayout.cpp FTSimpleLayoutImpl.h \
	FTSize.cpp FTSize.h \
	FTTextureGlyph.cpp FTTextureGlyph.h \
	FTVector.h \
	FTVectoriser.cpp FTVectoriser.h \
	$(ftgl_HEADERS)
libftgl_la_CPPFLAGS = -I$(top_srcdir)/include
libftgl_la_CXXFLAGS = $(FT2_CFLAGS) $(GL_CFLAGS)
libftgl_la_LDFLAGS = \
        $(FT2_LIBS) $(GL_LIBS) -no-undefined -version-number @LT_VERSION@

ftgldir = $(includedir)/FTGL
ftgl_HEADERS = \
	../include/ftgl.h \
	../include/FTFont.h \
	../include/FTGLBitmapFont.h \
	../include/FTGLExtrdFont.h \
	../include/FTGLOutlineFont.h \
	../include/FTGLPixmapFont.h \
	../include/FTGLPolygonFont.h \
	../include/FTGLTextureFont.h \
	../include/FTLayout.h \
	../include/FTSimpleLayout.h \
	${NULL}

NULL =
