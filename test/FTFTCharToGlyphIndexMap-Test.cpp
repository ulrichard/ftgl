#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

#include "FTCharToGlyphIndexMap.h"


class FTCharToGlyphIndexMapTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTCharToGlyphIndexMapTest);
        CPPUNIT_TEST( testConstructor);
        CPPUNIT_TEST( testInsert);
        CPPUNIT_TEST( testClear);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTCharToGlyphIndexMapTest() : CppUnit::TestCase( "FTCharToGlyphIndexMap Test")
        {}
        
        FTCharToGlyphIndexMapTest( const std::string& name) : CppUnit::TestCase(name) {}

        void testConstructor()
        {
            FTCharToGlyphIndexMap testMap;
            
            CPPUNIT_ASSERT( testMap.find( 2) == NULL);
            CPPUNIT_ASSERT( testMap.find( 5) == NULL);
        }
        
        void testInsert()
        {
            FTCharToGlyphIndexMap testMap;
            
            testMap.insert( 2, 37);
            
            CPPUNIT_ASSERT( *(testMap.find( 2)) == 37);
            CPPUNIT_ASSERT( testMap.find( 5) == NULL);
        }
        
        void testClear()
        {
            FTCharToGlyphIndexMap testMap;
            
            testMap.insert( 2, 37);
            testMap.clear();
            
            CPPUNIT_ASSERT( testMap.find( 2) == NULL);
            CPPUNIT_ASSERT( testMap.find( 5) == NULL);
        }
        
        
        void setUp() 
        {}
        
        
        void tearDown() 
        {}
        
    private:
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTCharToGlyphIndexMapTest);

