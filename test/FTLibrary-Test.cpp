#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

#include "FTLibrary.h"

class FTLibraryTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTLibraryTest);
        CPPUNIT_TEST( testConstructor);
        CPPUNIT_TEST( testError);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTLibraryTest() : CppUnit::TestCase( "FTLibrary Test")
        {}
        
        FTLibraryTest( const std::string& name) : CppUnit::TestCase(name) {}

        void testConstructor()
        {
            FTLibrary& libraryOne = FTLibrary::Instance();
            FTLibrary& libraryTwo = FTLibrary::Instance();
            
            CPPUNIT_ASSERT( &libraryOne == &libraryTwo);
            CPPUNIT_ASSERT( &libraryOne == &FTLibrary::Instance());
        }
        
        
        void testError()
        {
            FTLibrary& library = FTLibrary::Instance();
            
            CPPUNIT_ASSERT( library.Error() == 0);
        }
        
        
        void setUp() 
        {}
        
        
        void tearDown() 
        {}
        
    private:
        
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTLibraryTest);

