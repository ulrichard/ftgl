#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <assert.h>

#include "Fontdefs.h"
#include "FTGLTextureFont.h"

extern void buildGLContext();

class FTGLTextureFontTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTGLTextureFontTest);
        CPPUNIT_TEST( testConstructor);
        CPPUNIT_TEST( testResizeBug);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTGLTextureFontTest() : CppUnit::TestCase( "FTGLTextureFontTest Test")
        {
        }
        
        FTGLTextureFontTest( const std::string& name) : CppUnit::TestCase(name) {}
        
        ~FTGLTextureFontTest()
        {
        }
        
        void testConstructor()
        {
            buildGLContext();
        
            FTGLTextureFont* textureFont = new FTGLTextureFont( FONT_FILE);            
            CPPUNIT_ASSERT( textureFont->Error() == 0);            
            CPPUNIT_ASSERT( glGetError() == GL_NO_ERROR);        
        }

        void testResizeBug()
        {
            buildGLContext();
        
            FTGLTextureFont* textureFont = new FTGLTextureFont( FONT_FILE);            
            CPPUNIT_ASSERT( textureFont->Error() == 0);
            
            textureFont->FaceSize(18);
            textureFont->Render("blah");

            textureFont->FaceSize(38);
            textureFont->Render("blah");
            
            CPPUNIT_ASSERT( glGetError() == GL_NO_ERROR);        
        }

        void setUp() 
        {}
        
        void tearDown() 
        {}
                    
    private:
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTGLTextureFontTest);

