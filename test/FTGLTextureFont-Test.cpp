#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <assert.h>

#include "Fontdefs.h"
#include "FTGLTextureFont.h"

extern void buildGLContext();

class FTGLPolygonFontTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTGLPolygonFontTest);
        CPPUNIT_TEST( testConstructor);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTGLPolygonFontTest() : CppUnit::TestCase( "FTGLPolygonFont Test")
        {
        }
        
        FTGLPolygonFontTest( const std::string& name) : CppUnit::TestCase(name) {}
        
        ~FTGLPolygonFontTest()
        {
        }
        
        void testConstructor()
        {
//            buildGLContext();
        
            FTGLTextureFont* textureFont = new FTGLTextureFont( FONT_FILE);            
            CPPUNIT_ASSERT( textureFont->Error() == 0);
        
        }

        void setUp() 
        {}
        
        void tearDown() 
        {}
                    
    private:
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTGLPolygonFontTest);

