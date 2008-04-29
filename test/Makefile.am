
if HAVE_CPPUNIT
if HAVE_GLUT
noinst_PROGRAMS = FTGLTest
endif
endif

FTGLTest_SOURCES = \
    TestMain.cpp \
    Fontdefs.h \
    FTBBox-Test.cpp \
    FTBitmapGlyph-Test.cpp \
    FTCharmap-Test.cpp \
    FTCharToGlyphIndexMap-Test.cpp \
    FTContour-Test.cpp \
    FTExtrdGlyph-Test.cpp \
    FTFace-Test.cpp \
    FTGLBitmapFont-Test.cpp \
    FTGLExtrdFont-Test.cpp \
    FTGLOutlineFont-Test.cpp \
    FTGLPixmapFont-Test.cpp \
    FTGLPolygonFont-Test.cpp \
    FTGLTextureFont-Test.cpp \
    FTLibrary-Test.cpp \
    FTList-Test.cpp \
    FTMesh-Test.cpp \
    FTOutlineGlyph-Test.cpp \
    FTPixmapGlyph-Test.cpp \
    FTPoint-Test.cpp \
    FTPolyGlyph-Test.cpp \
    FTSize-Test.cpp \
    FTTesselation-Test.cpp \
    FTTextureGlyph-Test.cpp \
    FTVectoriser-Test.cpp \
    FTVector-Test.cpp \
    HPGCalc_afm.cpp \
    HPGCalc_pfb.cpp \
    $(NULL)
FTGLTest_CPPFLAGS = \
    -I$(top_srcdir)/include \
    -I$(top_srcdir)/src \
    -I$(top_srcdir)/src/FTGlyph \
    -I$(top_srcdir)/src/FTFont \
    -I$(top_srcdir)/src/FTLayout
FTGLTest_CXXFLAGS = $(FT2_CFLAGS) $(GL_CFLAGS)
FTGLTest_LDFLAGS = $(FT2_LIBS) $(GLUT_LIBS) -lcppunit
FTGLTest_LDADD = ../src/libftgl.la

DEACTIVATED = \
    FTFont-Test.cpp \
    FTGlyphContainer-Test.cpp \
    FTGlyph-Test.cpp \
    FTlayout-Test.cpp \
    $(NULL)

NULL =
