
lib_LTLIBRARIES = libftgl.la

libftgl_la_SOURCES = \
    FTBBox.h \
    FTCharmap.cpp \
    FTCharmap.h \
    FTCharToGlyphIndexMap.h \
    FTContour.cpp \
    FTContour.h \
    FTFace.cpp \
    FTFace.h \
    FTGlyphContainer.cpp \
    FTGlyphContainer.h \
    FTLibrary.cpp \
    FTLibrary.h \
    FTList.h \
    FTPoint.cpp \
    FTPoint.h \
    FTSize.cpp \
    FTSize.h \
    FTVector.h \
    FTVectoriser.cpp \
    FTVectoriser.h \
    $(ftglyph_sources) \
    $(ftfont_sources) \
    $(ftlayout_sources) \
    $(ftgl_headers) \
    $(NULL)
libftgl_la_CPPFLAGS = -IFTGlyph -IFTFont -IFTLayout -I$(top_srcdir)/include
libftgl_la_CXXFLAGS = $(FT2_CFLAGS) $(GL_CFLAGS)
libftgl_la_LDFLAGS = \
        $(FT2_LIBS) $(GL_LIBS) -no-undefined -version-number @LT_VERSION@

ftgldir = $(includedir)/FTGL
ftgl_HEADERS = $(ftgl_headers)

ftfont_headers = \
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

ftglyph_sources = \
    FTGlyph/FTGlyph.cpp \
    FTGlyph/FTGlyph.h \
    FTGlyph/FTGlyphGlue.cpp \
    FTGlyph/FTBitmapGlyph.cpp \
    FTGlyph/FTBitmapGlyph.h \
    FTGlyph/FTExtrdGlyph.cpp \
    FTGlyph/FTExtrdGlyph.h \
    FTGlyph/FTOutlineGlyph.cpp \
    FTGlyph/FTOutlineGlyph.h \
    FTGlyph/FTPixmapGlyph.cpp \
    FTGlyph/FTPixmapGlyph.h \
    FTGlyph/FTPolyGlyph.cpp \
    FTGlyph/FTPolyGlyph.h \
    FTGlyph/FTTextureGlyph.cpp \
    FTGlyph/FTTextureGlyph.h \
    $(NULL)

ftfont_sources = \
    FTFont/FTFont.cpp \
    FTFont/FTFontImpl.h \
    FTFont/FTFontGlue.cpp \
    FTFont/FTGLBitmapFont.cpp \
    FTFont/FTGLBitmapFontImpl.h \
    FTFont/FTGLExtrdFont.cpp \
    FTFont/FTGLExtrdFontImpl.h \
    FTFont/FTGLOutlineFont.cpp \
    FTFont/FTGLOutlineFontImpl.h \
    FTFont/FTGLPixmapFont.cpp \
    FTFont/FTGLPixmapFontImpl.h \
    FTFont/FTGLPolygonFont.cpp \
    FTFont/FTGLPolygonFontImpl.h \
    FTFont/FTGLTextureFont.cpp \
    FTFont/FTGLTextureFontImpl.h \
    $(NULL)

ftlayout_sources = \
    FTLayout/FTLayout.cpp \
    FTLayout/FTLayoutImpl.h \
    FTLayout/FTLayoutGlue.cpp \
    FTLayout/FTSimpleLayout.cpp \
    FTLayout/FTSimpleLayoutImpl.h \
    $(NULL)

NULL =
