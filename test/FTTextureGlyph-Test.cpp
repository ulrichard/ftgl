#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <assert.h>

#include "Fontdefs.h"
#include "FTTextureGlyph.h"

extern void buildGLContext();

class FTTextureGlyphTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE( FTTextureGlyphTest);
        CPPUNIT_TEST( testConstructor);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTTextureGlyphTest() : CppUnit::TestCase( "FTTextureGlyph Test")
        {
        }
        
        FTTextureGlyphTest( const std::string& name) : CppUnit::TestCase(name) {}
        
        ~FTTextureGlyphTest()
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
        
            FTTextureGlyph* textureGlyph = new FTTextureGlyph( face->glyph, 0, 0, 0, 0, 0);
         
            CPPUNIT_ASSERT( textureGlyph->Error() == 0);
        
            FT_Done_Face( face);
            FT_Done_FreeType( library);
            
            CPPUNIT_ASSERT( glGetError() == GL_NO_ERROR);        
        }

        void setUp() 
        {}
        
        void tearDown() 
        {}
                    
    private:
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTTextureGlyphTest);

