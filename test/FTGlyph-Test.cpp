#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

#include "FTList.h"


class FTGlyphTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTGlyphTest);
        CPPUNIT_TEST( testConstructor);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTGlyphTest() : CppUnit::TestCase( "FTGlyph Test")
        {}
        
        FTGlyphTest( const std::string& name) : CppUnit::TestCase(name) {}

        void testConstructor()
        {            
            CPPUNIT_ASSERT( false);
        }
        
                
        void setUp() 
        {}
        
        
        void tearDown() 
        {}
        
    private:
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTGlyphTest);

