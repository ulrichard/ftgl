#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <assert.h>

#include "Fontdefs.h"
#include "FTGLPixmapFont.h"

extern void buildGLContext();

class FTGLPixmapFontTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTGLPixmapFontTest);
        CPPUNIT_TEST( testConstructor);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTGLPixmapFontTest() : CppUnit::TestCase( "FTGLPixmapFont Test")
        {
        }
        
        FTGLPixmapFontTest( const std::string& name) : CppUnit::TestCase(name) {}
        
        ~FTGLPixmapFontTest()
        {
        }
        
        void testConstructor()
        {
            buildGLContext();
        
            FTGLPixmapFont* pixmapFont = new FTGLPixmapFont( FONT_FILE);            
            CPPUNIT_ASSERT( pixmapFont->Error() == 0);
        
            CPPUNIT_ASSERT( glGetError() == GL_NO_ERROR);        
        }

        void setUp() 
        {}
        
        void tearDown() 
        {}
                    
    private:
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTGLPixmapFontTest);

