#include    "FTGlyphContainer.h"
#include    "FTGlyph.h"
#include    "FTFace.h"
#include    "FTCharmap.h"


FTGlyphContainer::FTGlyphContainer( FTFace* f)
:   face(f),
    charMap(0),
    err(0)
{
    numberOfGlyphs = face->GlyphCount();

    if( 0 != numberOfGlyphs)
    {
        glyphs.resize( numberOfGlyphs, NULL);
        charMap = new FTCharmap( face);
    }
}


FTGlyphContainer::~FTGlyphContainer()
{
    GlyphVector::iterator glyphIterator;
    for( glyphIterator = glyphs.begin(); glyphIterator != glyphs.end(); ++glyphIterator)
    {
        delete *glyphIterator;
    }
    
    glyphs.clear();
}


bool FTGlyphContainer::CharMap( FT_Encoding encoding)
{
    bool result = charMap->CharMap( encoding);
    err = charMap->Error();
    return result;
}


unsigned int FTGlyphContainer::CharIndex( unsigned int characterCode) const
{
    return charMap->CharIndex( characterCode);
}


void FTGlyphContainer::Add( FTGlyph* tempGlyph, const unsigned int characterCode)
{
    unsigned int glyphIndex = charMap->CharIndex( characterCode);
    glyphs[glyphIndex] = tempGlyph;
}


const FTGlyph* const FTGlyphContainer::Glyph( const unsigned int characterCode) const
{
    return glyphs[charMap->CharIndex( characterCode)];
}


FTBBox FTGlyphContainer::BBox( const unsigned int characterCode) const
{
    return glyphs[charMap->CharIndex( characterCode)]->BBox();
}


float FTGlyphContainer::Advance( unsigned int characterCode, unsigned int nextCharacterCode)
{
    unsigned int left = charMap->CharIndex( characterCode);
    unsigned int right = charMap->CharIndex( nextCharacterCode);
    
    float width = face->KernAdvance( left, right).x;
    width += glyphs[left]->Advance();
    
    return width;
}


FTPoint FTGlyphContainer::Render( unsigned int characterCode, unsigned int nextCharacterCode, FTPoint penPosition)
{
    FTPoint kernAdvance;
    float advance = 0;
    
    unsigned int left = charMap->CharIndex( characterCode);
    unsigned int right = charMap->CharIndex( nextCharacterCode);
    
    kernAdvance = face->KernAdvance( left, right);
        
    if( !face->Error())
    {
        advance = glyphs[left]->Render( penPosition);
    }
    
    kernAdvance.x = advance + kernAdvance.x;
//  kernAdvance.y = advance.y + kernAdvance.y;
    return kernAdvance;
}
