#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <assert.h>

#include "Fontdefs.h"
#include "FTGLBitmapFont.h"

extern void buildGLContext();

class FTGLBitmapFontTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTGLBitmapFontTest);
        CPPUNIT_TEST( testConstructor);
        CPPUNIT_TEST( testRender);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTGLBitmapFontTest() : CppUnit::TestCase( "FTGLBitmapFont Test")
        {
        }
        
        FTGLBitmapFontTest( const std::string& name) : CppUnit::TestCase(name) {}
        
        ~FTGLBitmapFontTest()
        {
        }
        
        void testConstructor()
        {
            buildGLContext();
        
            FTGLBitmapFont* bitmapFont = new FTGLBitmapFont( FONT_FILE);            
            CPPUNIT_ASSERT( bitmapFont->Error() == 0);
        
            CPPUNIT_ASSERT( glGetError() == GL_NO_ERROR);        
        }

        void testRender()
        {
            buildGLContext();
        
            FTGLBitmapFont* bitmapFont = new FTGLBitmapFont( FONT_FILE);            
            bitmapFont->Render(GOOD_ASCII_TEST_STRING);

            CPPUNIT_ASSERT( bitmapFont->Error() == 0);        
            CPPUNIT_ASSERT( glGetError() == GL_NO_ERROR);        

            bitmapFont->FaceSize(18);
            bitmapFont->Render(GOOD_ASCII_TEST_STRING);

            CPPUNIT_ASSERT( bitmapFont->Error() == 0);        
            CPPUNIT_ASSERT( glGetError() == GL_NO_ERROR);        
        }

        void setUp() 
        {}
        
        void tearDown() 
        {}
                    
    private:
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTGLBitmapFontTest);

