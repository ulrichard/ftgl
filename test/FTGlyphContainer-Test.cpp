#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

#include "FTFace.h"
#include "FTGlyph.h"
#include "FTGlyphContainer.h"


static const char* GOOD_FONT_FILE = "../../test/MHei-Medium-Acro";
static const unsigned int NUMBER_OF_GLYPHS = 50;
static const unsigned int TOO_MANY_GLYPHS = 14100; // MHei-Medium-Acro has 14099

static const unsigned int FONT_INDEX_OF_A = 34;


class TestGlyph : public FTGlyph
{
    public:
        TestGlyph()
        :   FTGlyph(0)
        {
            advance = 50.0f;
        }
        
        virtual float Render( const FTPoint& pen){ return advance;}
};


class FTGlyphContainerTest : public CppUnit::TestCase
{
        CPPUNIT_TEST_SUITE( FTGlyphContainerTest);
            CPPUNIT_TEST( testAdd);
            CPPUNIT_TEST( testAdvance);
            CPPUNIT_TEST( testRender);
        CPPUNIT_TEST_SUITE_END();
        
    public:
        FTGlyphContainerTest() : CppUnit::TestCase( "FTGlyphContainer Test")
        {
            face = new FTFace;
            face->Open( GOOD_FONT_FILE);
            face->Size( 72, 72);
            face->CharMap( ft_encoding_unicode);
        }
        
        FTGlyphContainerTest( const std::string& name) : CppUnit::TestCase(name)
        {
            delete face;
        }

        void testAdd()
        {
            TestGlyph* glyph = new TestGlyph();
            CPPUNIT_ASSERT( !glyphContainer->Add( glyph, TOO_MANY_GLYPHS));
            CPPUNIT_ASSERT( glyphContainer->Add( glyph, FONT_INDEX_OF_A));
            
            CPPUNIT_ASSERT( glyphContainer->Glyph( 'A') == glyph);
        }
        
        
        void testAdvance()
        {
            TestGlyph* glyph = new TestGlyph();

            CPPUNIT_ASSERT( glyphContainer->Add( glyph, FONT_INDEX_OF_A));
            
            float advance = glyphContainer->Advance( 'A', 0);
            
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 50, advance, 0.01);
        }
        
        
        void testRender()
        {
            TestGlyph* glyph = new TestGlyph();
            
            CPPUNIT_ASSERT( glyphContainer->Add( glyph, FONT_INDEX_OF_A));
            
            FTPoint pen;
            
            float advance = glyphContainer->Render( 'A', 0, pen).x;
            
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 50, advance, 0.01);
        }
        
        
        void setUp() 
        {
            glyphContainer = new FTGlyphContainer( face);
        }
        
        
        void tearDown() 
        {
            delete glyphContainer;
            delete face;
        }
        
    private:
        FTFace* face;
        FTGlyphContainer* glyphContainer;
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTGlyphContainerTest);

