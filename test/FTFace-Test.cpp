#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestCaller.h"
#include "cppunit/TestCase.h"
#include "cppunit/TestSuite.h"

#include "Fontdefs.h"
#include "FTFace.h"


class FTFaceTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTFaceTest);
        CPPUNIT_TEST( testOpenFace);
        CPPUNIT_TEST( testOpenFaceFromMemory);
        CPPUNIT_TEST( testAttachFile);
        CPPUNIT_TEST( testGlyphCount);
        CPPUNIT_TEST( testSetFontSize);
        CPPUNIT_TEST( testSetCharMap);
        CPPUNIT_TEST( testCharacterIndex);
        CPPUNIT_TEST( testKerning);
    CPPUNIT_TEST_SUITE_END();

  public:
    FTFaceTest() : CppUnit::TestCase( "FTFace test") {};
    FTFaceTest( const std::string& name) : CppUnit::TestCase(name) {};
    

    void testOpenFace()
    {
        CPPUNIT_ASSERT( !testFace->Open( BAD_FONT_FILE));
        CPPUNIT_ASSERT( testFace->Error() == 1);        

        CPPUNIT_ASSERT( testFace->Open( GOOD_FONT_FILE));
        CPPUNIT_ASSERT( testFace->Error() == 0);        
    }
    
    
    void testOpenFaceFromMemory()
    {
        CPPUNIT_ASSERT( !testFace->Open( (unsigned char*)100, 0));
        CPPUNIT_ASSERT( testFace->Error() == 85);        

        CPPUNIT_ASSERT( testFace->Open( arial_ttf.dataBytes, arial_ttf.numBytes));
        CPPUNIT_ASSERT( testFace->Error() == 0);        
    }
    
    
    void testAttachFile()
    {
        CPPUNIT_ASSERT( testFace->Open( GOOD_FONT_FILE));
        CPPUNIT_ASSERT( testFace->Error() == 0);
                
        CPPUNIT_ASSERT( !testFace->Attach( GOOD_FONT_FILE));
        CPPUNIT_ASSERT( testFace->Error() == 7);        
    }
    

    void testGlyphCount()
    {
        CPPUNIT_ASSERT( testFace->Open( GOOD_FONT_FILE));
        CPPUNIT_ASSERT( testFace->Error() == 0);
                
        CPPUNIT_ASSERT(testFace->GlyphCount() == 14099);        
    }
    

    void testSetFontSize()
    {
        testFace->Open( GOOD_FONT_FILE);
        
        FTSize size = testFace->Size( GOOD_SIZE, RESOLUTION);
        CPPUNIT_ASSERT( testFace->Error() == 0);
    }
    
    
    void testSetCharMap()
    {
        testFace->Open( GOOD_FONT_FILE);
    
        CPPUNIT_ASSERT( testFace->CharMap( ft_encoding_unicode));
        CPPUNIT_ASSERT( testFace->Error() == 0);
        
        CPPUNIT_ASSERT( !testFace->CharMap( ft_encoding_johab));
        CPPUNIT_ASSERT( testFace->Error() == 6);
    }
    
    
    void testCharacterIndex()
    {
        testFace->Open( GOOD_FONT_FILE);

        CPPUNIT_ASSERT( testFace->CharIndex( 'A') == 34);
        CPPUNIT_ASSERT( testFace->CharIndex( 0x6FB3) == 4838);
    }
    
    
    void testKerning()
    {
        testFace->Open( GOOD_FONT_FILE);
    
        FTPoint kerningVector = testFace->KernAdvance( 'A', 'W');
        CPPUNIT_ASSERT( kerningVector.x == 0);
        CPPUNIT_ASSERT( kerningVector.y == 0);
        CPPUNIT_ASSERT( kerningVector.z == 0);
    
        kerningVector = testFace->KernAdvance( 0x6FB3, 0x9580);
        CPPUNIT_ASSERT( kerningVector.x == 0);
        CPPUNIT_ASSERT( kerningVector.y == 0);
        CPPUNIT_ASSERT( kerningVector.z == 0);
    }
    
    
    void setUp() 
    {
        testFace = new FTFace;
    }


    void tearDown() 
    {
        delete testFace;
    }
    
  private:
        FTFace* testFace;

};

CPPUNIT_TEST_SUITE_REGISTRATION( FTFaceTest);

