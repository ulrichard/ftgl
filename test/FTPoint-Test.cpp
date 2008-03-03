#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

#include "FTPoint.h"


class FTPointTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTPointTest);
        CPPUNIT_TEST( testConstructor);
        CPPUNIT_TEST( testOperatorEqual);
        CPPUNIT_TEST( testOperatorNotEqual);
        CPPUNIT_TEST( testOperatorPlusEquals);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTPointTest() : CppUnit::TestCase( "FTPoint Test")
        {}
        
        FTPointTest( const std::string& name) : CppUnit::TestCase(name) {}
        
        void testConstructor()
        {
            FTPoint point1;

            CPPUNIT_ASSERT( point1.x == 0.0f);
            CPPUNIT_ASSERT( point1.y == 0.0f);
            CPPUNIT_ASSERT( point1.z == 0.0f);
            
            FTPoint point2( 1.0f, 2.0f, 3.0f);

            CPPUNIT_ASSERT( point2.x == 1.0f);
            CPPUNIT_ASSERT( point2.y == 2.0f);
            CPPUNIT_ASSERT( point2.z == 3.0f);
            
            FT_Vector ftVector;
            ftVector.x = 4;
            ftVector.y = 23;
            
            FTPoint point3( ftVector);
            
            CPPUNIT_ASSERT( point3.x ==  4.0f);
            CPPUNIT_ASSERT( point3.y == 23.0f);
            CPPUNIT_ASSERT( point3.z ==  0.0f); 
        }

        
        void testOperatorEqual()
        {
            FTPoint point1(  1.0f, 2.0f, 3.0f);
            FTPoint point2(  1.0f, 2.0f, 3.0f);
            FTPoint point3( -1.0f, 2.3f, 23.0f);
            
            CPPUNIT_ASSERT(   point1 == point1);
            CPPUNIT_ASSERT(   point1 == point2);
            CPPUNIT_ASSERT( !(point1 == point3));
        }
        
        
        void testOperatorNotEqual()
        {
            FTPoint point1(  1.0f, 2.0f, 3.0f);
            FTPoint point2(  1.0f, 2.0f, 3.0f);
            FTPoint point3( -1.0f, 2.3f, 23.0f);
            
            CPPUNIT_ASSERT( !(point1 != point1));
            CPPUNIT_ASSERT( !(point1 != point2));
            CPPUNIT_ASSERT(   point1 != point3);
        }
        
        
        void testOperatorPlusEquals()
        {
            FTPoint point1(  1.0f, 2.0f, 3.0f);
            FTPoint point2(  -2.0f, 21.0f, 0.0f);
            FTPoint point3( -1.0f, 23.0f, 3.0f);
            
            point1 += point2;
            
            CPPUNIT_ASSERT( point1 == point3);
        }
        
        
        void setUp() 
        {}
        
        
        void tearDown() 
        {}
        
    private:
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTPointTest);

