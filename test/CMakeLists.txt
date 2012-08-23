
FIND_PACKAGE(CxxTest  REQUIRED)
FIND_PACKAGE(GLUT     REQUIRED)

SET(CXXTEST_USE_PYTHON TRUE)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/cmake)
INCLUDE_DIRECTORIES(${CXXTEST_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CXXTEST_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR})

ADD_DEFINITIONS(-D HAVE_GL_GLUT_H)

ENABLE_TESTING()

ADD_EXECUTABLE(FTGL_testsC CTest.c)
TARGET_LINK_LIBRARIES(FTGL_testsC
   ftgl
#	cppunit
	${FREETYPE_LIBRARIES}
	${OPENGL_LIBRARIES}
	${GLUT_LIBRARIES}
)

SET_TARGET_PROPERTIES(FTGL_testsC
  PROPERTIES
    VERSION ${VERSION_SERIES}.${VERSION_MAJOR}.${VERSION_MINOR}
	SOVERSION ${FTGL_SOVERSION}
   DEBUG_POSTFIX "d"
)


SET(CXXTest_SOURCES
#    $(DEACTIVATED)
    CXXTest.cpp
#    Fontdefs.h
#    FTBBox-Test.cpp
#    FTBitmapFont-Test.cpp
    FTBitmapGlyph-Test.cpp
    FTCharmap-Test.cpp
    FTCharToGlyphIndexMap-Test.cpp
#    FTContour-Test.cpp
    FTExtrudeFont-Test.cpp
    FTExtrudeGlyph-Test.cpp
##    FTFace-Test.cpp
#    FTFont-Test.cpp
#    FTGlyph-Test.cpp
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
#    FTSize-Test.cpp
    FTTesselation-Test.cpp
#    FTTextureFont-Test.cpp
    FTTextureGlyph-Test.cpp
#    FTVectoriser-Test.cpp
    FTVector-Test.cpp
    HPGCalc_afm.cpp
    HPGCalc_pfb.cpp

	FTTriangleExtract-Test.cpp
)

#CXXTEST_ADD_TEST(FTGL_tests ${CXXTest_SOURCES})

#CXXTEST_ADD_TEST(FTGL_tests FTBBox-Test.cpp)


ADD_EXECUTABLE(FTGL_tests ${CXXTest_SOURCES})
TARGET_LINK_LIBRARIES(FTGL_tests
   ftgl
	cppunit
	${FREETYPE_LIBRARIES}
	${OPENGL_LIBRARIES}
	${GLUT_LIBRARIES}
)

SET_TARGET_PROPERTIES(FTGL_tests
  PROPERTIES
    VERSION ${VERSION_SERIES}.${VERSION_MAJOR}.${VERSION_MINOR}
	SOVERSION ${FTGL_SOVERSION}
   DEBUG_POSTFIX "d"
)

ADD_EXECUTABLE(demo demo.cpp)
TARGET_LINK_LIBRARIES(demo
   ftgl
	${FREETYPE_LIBRARIES}
	${OPENGL_LIBRARIES}
	${GLUT_LIBRARIES}
)

SET_TARGET_PROPERTIES(demo
  PROPERTIES
    VERSION ${VERSION_SERIES}.${VERSION_MAJOR}.${VERSION_MINOR}
	SOVERSION ${FTGL_SOVERSION}
   DEBUG_POSTFIX "d"
)


