#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>


#include "Fontdefs.h"
#include "FTFace.h"
#include "FTGlyph.h"
#include "FTGlyphContainer.h"


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
        CPPUNIT_TEST( testSetCharMap);
        CPPUNIT_TEST( testCharacterIndex);
        CPPUNIT_TEST( testAdvance);
        CPPUNIT_TEST( testRender);
    CPPUNIT_TEST_SUITE_END();
        
    public:
        FTGlyphContainerTest() : CppUnit::TestCase( "FTGlyphContainer Test")
        {
            face = new FTFace( GOOD_FONT_FILE);
            face->Size( 72, 72);
        }
        
        FTGlyphContainerTest( const std::string& name) : CppUnit::TestCase(name)
        {
            delete face;
        }

        void testAdd()
        {
            TestGlyph* glyph = new TestGlyph();
            glyphContainer->Add( glyph, 'A');
            glyphContainer->Add( 0, 0);

            CPPUNIT_ASSERT( glyphContainer->Glyph( 0) == 0);
            CPPUNIT_ASSERT( glyphContainer->Glyph( 'A') == glyph);
        }

    
        void testSetCharMap()
        {
            CPPUNIT_ASSERT( glyphContainer->CharMap( ft_encoding_unicode));
            CPPUNIT_ASSERT( glyphContainer->Error() == 0);
    
            CPPUNIT_ASSERT( !glyphContainer->CharMap( ft_encoding_johab));
            CPPUNIT_ASSERT( glyphContainer->Error() == 6);
        }


        void testCharacterIndex()
        {
            CPPUNIT_ASSERT( glyphContainer->CharIndex( 'A') == 34);
            CPPUNIT_ASSERT( glyphContainer->CharIndex( 0x6FB3) == 4838);
        }    
        
        
        void testAdvance()
        {
            TestGlyph* glyph = new TestGlyph();

            glyphContainer->Add( glyph, 'A');
            float advance = glyphContainer->Advance( 'A', 0);
            
            CPPUNIT_ASSERT_DOUBLES_EQUAL( 50, advance, 0.01);
        }
        
        
        void testRender()
        {
            TestGlyph* glyph = new TestGlyph();
            
            glyphContainer->Add( glyph, 'A');
            
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
        FTFace*           face;
        FTGlyphContainer* glyphContainer;

};

CPPUNIT_TEST_SUITE_REGISTRATION( FTGlyphContainerTest);

