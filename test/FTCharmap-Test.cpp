#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTCharmap.h"

static const unsigned int CHARACTER_CODE      =    'A';
static const unsigned int BIG_CHARACTER_CODE  = 0x6FB3;
static const unsigned int NULL_CHARACTER_CODE =    512;

static const unsigned int FONT_INDEX      =   34;
static const unsigned int BIG_FONT_INDEX  = 4838;
static const unsigned int NULL_FONT_INDEX =    0;

static const std::string FONT_FILE = "../../test/MHei-Medium-Acro";

class FTCharmapTest : public CppUnit::TestCase
{
        CPPUNIT_TEST_SUITE( FTCharmapTest);
            CPPUNIT_TEST( testConstructor);
            CPPUNIT_TEST( testSetEncoding);
            CPPUNIT_TEST( testGetCharacterIndex);
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
            CPPUNIT_ASSERT( charmap->CharIndex( CHARACTER_CODE)      == FONT_INDEX);
            CPPUNIT_ASSERT( charmap->CharIndex( BIG_CHARACTER_CODE)  == BIG_FONT_INDEX);
            CPPUNIT_ASSERT( charmap->CharIndex( NULL_CHARACTER_CODE) == NULL_FONT_INDEX);
            
            charmap->CharMap( ft_encoding_johab);
            
            CPPUNIT_ASSERT( charmap->Error() == 6);
            CPPUNIT_ASSERT( charmap->CharIndex( CHARACTER_CODE)      == FONT_INDEX);
            CPPUNIT_ASSERT( charmap->CharIndex( BIG_CHARACTER_CODE)  == BIG_FONT_INDEX);
            CPPUNIT_ASSERT( charmap->CharIndex( NULL_CHARACTER_CODE) == NULL_FONT_INDEX);
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
        FT_Library   library;
        FT_Face      face;
        
        FTCharmap* charmap;

        void setUpFreetype()
        {
            FT_Error error = FT_Init_FreeType( &library);
            assert(!error);
            error = FT_New_Face( library, FONT_FILE.c_str(), 0, &face);
            assert(!error);
        }
        
        void tearDownFreetype()
        {
            FT_Done_Face( face);
            FT_Done_FreeType( library);
        }
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTCharmapTest);

