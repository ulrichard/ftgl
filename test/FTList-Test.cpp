#include <iostream>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

#include "FTList.h"


class FTListTest : public CppUnit::TestCase
{
        CPPUNIT_TEST_SUITE( FTListTest);
            CPPUNIT_TEST( testConstructor);
            CPPUNIT_TEST( testPushBack);
            CPPUNIT_TEST( testGetBack);
        CPPUNIT_TEST_SUITE_END();
        
    public:
        FTListTest() : CppUnit::TestCase( "FTList Test")
        {}
        
        FTListTest( const std::string& name) : CppUnit::TestCase(name) {}

        void testConstructor()
        {
            FTList<float> listOfFloats;
            
            CPPUNIT_ASSERT( listOfFloats.size() == 0);
        }
        
        
        void testPushBack()
        {
            FTList<float> listOfFloats;
            
            CPPUNIT_ASSERT( listOfFloats.size() == 0);
            
            listOfFloats.push_back( 0.1);
            listOfFloats.push_back( 1.2);
            listOfFloats.push_back( 2.3);

            CPPUNIT_ASSERT( listOfFloats.size() == 3);            
        }
        
        
        void testGetBack()
        {
            FTList<float> listOfFloats;
            
            listOfFloats.push_back( 0.1);
            listOfFloats.push_back( 1.2);
            listOfFloats.push_back( 2.3);

            std::cout << listOfFloats.back() << std::endl;
            CPPUNIT_ASSERT( listOfFloats.back() == 2.3);            
        }
        
        
        void setUp() 
        {}
        
        
        void tearDown() 
        {}
        
    private:
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTListTest);

