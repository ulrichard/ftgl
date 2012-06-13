
FIND_PACKAGE(CxxTest  REQUIRED)

INCLUDE_DIRECTORIES(${CXXTEST_INCLUDE_DIRS})

SET(CXXTest_SOURCES
    $(DEACTIVATED)
    CXXTest.cpp
    Fontdefs.h
    FTBBox-Test.cpp
    FTBitmapFont-Test.cpp
    FTBitmapGlyph-Test.cpp
    FTCharmap-Test.cpp
    FTCharToGlyphIndexMap-Test.cpp
    FTContour-Test.cpp
    FTExtrudeFont-Test.cpp
    FTExtrudeGlyph-Test.cpp
    FTFace-Test.cpp
    FTFont-Test.cpp
    FTGlyph-Test.cpp
    FTGlyphContainer-Test.cpp
    FTlayout-Test.cpp
    FTLibrary-Test.cpp
    FTList-Test.cpp
    FTMesh-Test.cpp
    FTOutlineFont-Test.cpp
    FTOutlineGlyph-Test.cpp
    FTPixmapFont-Test.cpp
    FTPixmapGlyph-Test.cpp
    FTPoint-Test.cpp
    FTPolygonFont-Test.cpp
    FTPolygonGlyph-Test.cpp
    FTSize-Test.cpp
    FTTesselation-Test.cpp
    FTTextureFont-Test.cpp
    FTTextureGlyph-Test.cpp
    FTVectoriser-Test.cpp
    FTVector-Test.cpp
    HPGCalc_afm.cpp
    HPGCalc_pfb.cpp
)


ADD_EXECUTABLE(CXXTest ${CXXTest_SOURCES})
TARGET_LINK_LIBRARIES(CXXTest
    ftgl
	cppunit
	${FREETYPE_LIBRARIES}
	${OPENGL_LIBRARIES}
)

SET_TARGET_PROPERTIES(
    CXXTest
  PROPERTIES
    VERSION ${VERSION_SERIES}.${VERSION_MAJOR}.${VERSION_MINOR}
	SOVERSION ${FTGL_SOVERSION}
    DEBUG_POSTFIX "d"
)




