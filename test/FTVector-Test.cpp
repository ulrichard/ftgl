#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

#include "FTVector.h"


class FTVectorTest : public CppUnit::TestCase
{
        CPPUNIT_TEST_SUITE( FTVectorTest);
            CPPUNIT_TEST( testConstructor);
        CPPUNIT_TEST_SUITE_END();
        
    public:
        FTVectorTest() : CppUnit::TestCase( "FTVector Test")
        {}
        
        FTVectorTest( const std::string& name) : CppUnit::TestCase(name) {}

        void testConstructor()
        {
        }
        
        
        void setUp() 
        {}
        
        
        void tearDown() 
        {}
        
    private:
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTVectorTest);

