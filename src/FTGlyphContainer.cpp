#include    "FTGlyphContainer.h"
#include    "FTGlyph.h"
#include    "FTFace.h"


FTGlyphContainer::FTGlyphContainer( FTFace* f)
:   face(f),
    err(0)
{
    numberOfGlyphs = face->GlyphCount();
    glyphs.resize( numberOfGlyphs, NULL);
}


FTGlyphContainer::~FTGlyphContainer()
{
    GlyphVector::iterator iter;
    for( iter = glyphs.begin(); iter != glyphs.end(); ++iter)
    {
        if( *iter)
        {
            delete *iter;
        }
    }
    
    glyphs.clear();
}


bool FTGlyphContainer::Add( FTGlyph* tempGlyph, unsigned int glyphIndex)
{
    if( glyphIndex >= numberOfGlyphs)
    {
        return false;
    }
    
    glyphs[glyphIndex] = tempGlyph;
    return true;
}


const FTGlyph* const FTGlyphContainer::Glyph( const unsigned int characterCode) const
{
    return glyphs[face->CharIndex( characterCode)];
}


FTBBox FTGlyphContainer::BBox( const unsigned int characterCode) const
{
    return glyphs[face->CharIndex( characterCode)]->BBox();
}


float FTGlyphContainer::Advance( unsigned int characterCode, unsigned int nextCharacterCode)
{
    unsigned int left = face->CharIndex( characterCode);
    unsigned int right = face->CharIndex( nextCharacterCode);
    
    float width = face->KernAdvance( left, right).x;
    width += glyphs[left]->Advance();
    
    return width;
}


FTPoint FTGlyphContainer::Render( unsigned int characterCode, unsigned int nextCharacterCode, FTPoint penPosition)
{
    FTPoint kernAdvance;
    float advance = 0;
    
    unsigned int left = face->CharIndex( characterCode);
    unsigned int right = face->CharIndex( nextCharacterCode);
    
    kernAdvance = face->KernAdvance( left, right);
        
    if( !face->Error())
    {
        advance = glyphs[left]->Render( penPosition);
    }
    
    kernAdvance.x = advance + kernAdvance.x;
//  kernAdvance.y = advance.y + kernAdvance.y;
    return kernAdvance;
}
