#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <assert.h>

#include "Fontdefs.h"
#include "FTGLOutlineFont.h"

extern void buildGLContext();

class FTGLOutlineFontTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTGLOutlineFontTest);
        CPPUNIT_TEST( testConstructor);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTGLOutlineFontTest() : CppUnit::TestCase( "FTGLOutlineFont Test")
        {
        }
        
        FTGLOutlineFontTest( const std::string& name) : CppUnit::TestCase(name) {}
        
        ~FTGLOutlineFontTest()
        {
        }
        
        void testConstructor()
        {
            buildGLContext();
        
            FTGLOutlineFont* outlineFont = new FTGLOutlineFont( FONT_FILE);            
            CPPUNIT_ASSERT( outlineFont->Error() == 0);
        
            CPPUNIT_ASSERT( glGetError() == GL_NO_ERROR);        
        }

        void setUp() 
        {}
        
        void tearDown() 
        {}
                    
    private:
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTGLOutlineFontTest);

