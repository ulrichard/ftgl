#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <assert.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H


#include "Fontdefs.h"
#include "FTFace.h"
#include "FTCharmap.h"


class FTCharmapTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTCharmapTest);
        CPPUNIT_TEST( testConstructor);
        CPPUNIT_TEST( testSetEncoding);
        CPPUNIT_TEST( testGetCharacterIndex);
        CPPUNIT_TEST( testGetGlyphIndex);
        CPPUNIT_TEST( testInsertCharacterIndex);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTCharmapTest() : CppUnit::TestCase( "FTCharmap Test")
        {
            setUpFreetype();
        }
        
        FTCharmapTest( const std::string& name) : CppUnit::TestCase(name) {}
        
        ~FTCharmapTest()
        {
            tearDownFreetype();
        }
        
        
        void testConstructor()
        {
            CPPUNIT_ASSERT( charmap->Error() == 0);
            CPPUNIT_ASSERT( charmap->Encoding() == ft_encoding_unicode);
        }
        
        
        void testSetEncoding()
        {
            CPPUNIT_ASSERT( charmap->CharMap( ft_encoding_unicode));
            
            CPPUNIT_ASSERT( charmap->Error() == 0);
            CPPUNIT_ASSERT( charmap->Encoding() == ft_encoding_unicode);
            
            CPPUNIT_ASSERT( !charmap->CharMap( ft_encoding_johab));
            
            CPPUNIT_ASSERT( charmap->Error() == 6);
            CPPUNIT_ASSERT( charmap->Encoding() == ft_encoding_none);
        }
        
        
        void testGetCharacterIndex()
        {
            charmap->CharMap( ft_encoding_unicode);
            
            CPPUNIT_ASSERT( charmap->Error() == 0);
            CPPUNIT_ASSERT( charmap->CharIndex( CHARACTER_CODE_A)    == 0);
            CPPUNIT_ASSERT( charmap->CharIndex( BIG_CHARACTER_CODE)  == 0);
            CPPUNIT_ASSERT( charmap->CharIndex( NULL_CHARACTER_CODE) == 0);
            
            charmap->CharMap( ft_encoding_johab);
            
            CPPUNIT_ASSERT( charmap->Error() == 6);
            CPPUNIT_ASSERT( charmap->CharIndex( CHARACTER_CODE_A)    == 0);
            CPPUNIT_ASSERT( charmap->CharIndex( BIG_CHARACTER_CODE)  == 0);
            CPPUNIT_ASSERT( charmap->CharIndex( NULL_CHARACTER_CODE) == 0);
        }

    
        void testGetGlyphIndex()
        {
            charmap->CharMap( ft_encoding_unicode);

            CPPUNIT_ASSERT( charmap->Error() == 0);
            CPPUNIT_ASSERT( charmap->GlyphIndex( CHARACTER_CODE_A)    == FONT_INDEX_OF_A);
            CPPUNIT_ASSERT( charmap->GlyphIndex( BIG_CHARACTER_CODE)  == BIG_FONT_INDEX);
            CPPUNIT_ASSERT( charmap->GlyphIndex( NULL_CHARACTER_CODE) == NULL_FONT_INDEX);
        }
    
    
        void testInsertCharacterIndex()
        {
            CPPUNIT_ASSERT( charmap->CharIndex( CHARACTER_CODE_A) == 0);

            charmap->InsertIndex( CHARACTER_CODE_A, charmap->GlyphIndex( CHARACTER_CODE_A));
            CPPUNIT_ASSERT( charmap->CharIndex( CHARACTER_CODE_A) == FONT_INDEX_OF_A);

            charmap->InsertIndex( CHARACTER_CODE_A, 999);
            CPPUNIT_ASSERT( charmap->CharIndex( CHARACTER_CODE_A) == 999);
        }
        
        
        void setUp() 
        {
            charmap = new FTCharmap( face);
        }
        
        
        void tearDown() 
        {
            delete charmap;
        }
        
    private:
        FTFace*      face;
        FTCharmap* charmap;

        void setUpFreetype()
        {
            face = new FTFace( GOOD_FONT_FILE);
            CPPUNIT_ASSERT( !face->Error());
        }
        
        void tearDownFreetype()
        {
            delete face;
        }
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTCharmapTest);

