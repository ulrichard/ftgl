#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <assert.h>

#include "Fontdefs.h"
#include "FTGLExtrdFont.h"

extern void buildGLContext();

class FTGLExtrdFontTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTGLExtrdFontTest);
        CPPUNIT_TEST( testConstructor);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTGLExtrdFontTest() : CppUnit::TestCase( "FTGLExtrdFont Test")
        {
        }
        
        FTGLExtrdFontTest( const std::string& name) : CppUnit::TestCase(name) {}
        
        ~FTGLExtrdFontTest()
        {
        }
        
        void testConstructor()
        {
            buildGLContext();
        
            FTGLExtrdFont* extrudedFont = new FTGLExtrdFont( FONT_FILE);            
            CPPUNIT_ASSERT( extrudedFont->Error() == 0);
        
            CPPUNIT_ASSERT( glGetError() == GL_NO_ERROR);        
        }

        void setUp() 
        {}
        
        void tearDown() 
        {}
                    
    private:
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTGLExtrdFontTest);

