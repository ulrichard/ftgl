#include <cassert>

#include "FTICUFace.h"


FTICUFace::FTICUFace( const char* filename)
:   face( filename)
{
    err = face.Error();
}


FTICUFace::FTICUFace( const unsigned char *pBufferBytes, size_t bufferSizeInBytes)
:   face( pBufferBytes, bufferSizeInBytes)
{
    err = face.Error();
}

FTICUFace::~FTICUFace()
{}


const void* FTICUFace::getFontTable( LETag tableTag) const
{
    assert( false);
}

le_bool FTICUFace::canDisplay( LEUnicode32 ch) const
{
    assert( false);
}

        
le_int32 FTICUFace::getUnitsPerEM() const
{
    return face.UnitsPerEM();
}
        
void FTICUFace::mapCharsToGlyphs( const LEUnicode chars[], le_int32 offset,
                                  le_int32 count, le_bool reverse, const LECharMapper *mapper,
                                  LEGlyphID glyphs[]) const
{
    assert( false);
}

        
LEGlyphID FTICUFace::mapCharToGlyph( LEUnicode32 ch, const LECharMapper *mapper) const
{
    assert( false);
}

        
le_int32 FTICUFace::getName( le_uint16 platformID, le_uint16 scriptID, le_uint16 languageID,
                             le_uint16 nameID, LEUnicode *name) const
{
    assert( false);
}

        
void FTICUFace::getGlyphAdvance( LEGlyphID glyph, LEPoint &advance) const
{
    assert( false);
}

        
le_bool FTICUFace::getGlyphPoint( LEGlyphID glyph, le_int32 pointNumber, LEPoint &point) const
{
    assert( false);
}

        
float FTICUFace::getXPixelsPerEm() const
{
    assert( false);
}

        
float FTICUFace::getYPixelsPerEm() const
{
    assert( false);
}

        
float FTICUFace::xUnitsToPoints( float xUnits) const
{
    assert( false);
}

        
float FTICUFace::yUnitsToPoints( float yUunits) const
{
    assert( false);
}

        
void FTICUFace::unitsToPoints( LEPoint &units, LEPoint &points) const
{
    assert( false);
}

        
float FTICUFace::xPixelsToUnits( float xPixels) const
{
    assert( false);
}

        
float FTICUFace::yPixelsToUnits( float yPixels) const
{
    assert( false);
}

        
void FTICUFace::pixelsToUnits( LEPoint &pixels, LEPoint &units) const
{
    assert( false);
}

        
void FTICUFace::transformFunits( float xFunits, float yFunits, LEPoint &pixels) const
{
    assert( false);
}

