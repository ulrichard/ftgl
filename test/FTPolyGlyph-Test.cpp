#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <assert.h>

#include "Fontdefs.h"
#include "FTPolyGlyph.h"

extern void buildGLContext();

class FTPolyGlyphTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTPolyGlyphTest);
        CPPUNIT_TEST( testConstructor);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTPolyGlyphTest() : CppUnit::TestCase( "FTPolyGlyph Test")
        {
        }
        
        FTPolyGlyphTest( const std::string& name) : CppUnit::TestCase(name) {}
        
        ~FTPolyGlyphTest()
        {
        }
        
        void testConstructor()
        {
            FT_Library   library;
            FT_Face      face;
            
            FT_Error error = FT_Init_FreeType( &library);
            assert(!error);
            error = FT_New_Face( library, FONT_FILE, 0, &face);
            assert(!error);
            
            FT_Set_Char_Size( face, 0L, FONT_POINT_SIZE * 64, RESOLUTION, RESOLUTION);
            
            error = FT_Load_Char( face, CHARACTER_CODE_A, FT_LOAD_DEFAULT);
            assert( !error);
            
            buildGLContext();
        
            FTPolyGlyph* polyGlyph = new FTPolyGlyph( face->glyph);            
            CPPUNIT_ASSERT( polyGlyph->Error() == 0);
        
            FT_Done_Face( face);
            FT_Done_FreeType( library);
            
        }

        void setUp() 
        {}
        
        void tearDown() 
        {}
                    
    private:
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTPolyGlyphTest);

