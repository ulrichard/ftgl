#include    "FTFace.h"
#include    "FTFont.h"
#include    "FTGlyphContainer.h"
#include    "FTBBox.h"


FTFont::FTFont( const char* fontname)
:   numFaces(0),
    glyphList(0)
{
    if( face.Open( fontname))
    {
        err = 0;
    }
    else
    {
        err = face.Error();
    }
}


FTFont::FTFont( const unsigned char *pBufferBytes, size_t bufferSizeInBytes)
:   numFaces(0),
    glyphList(0)
{
    if( face.Open( pBufferBytes, bufferSizeInBytes ))
    {
        err = 0;
    }
    else
    {
        err = face.Error();
    }
}


FTFont::~FTFont()
{
    delete glyphList;
}


bool FTFont::Attach( const char* filename)
{
    if( face.Attach( filename))
    {
        err = 0;
        return true;
    }
    else
    {
        err = face.Error();
        return false;
    }
}


bool FTFont::FaceSize( const unsigned int size, const unsigned int res )
{
    charSize = face.Size( size, res);
    
    if( face.Error())
    {
        return false;
    }
    
    if( glyphList)
    {
        delete glyphList;
    }
    
    glyphList = new FTGlyphContainer( &face);
    
    return MakeGlyphList();
}


unsigned int FTFont::FaceSize() const
{
    return charSize.CharSize();
}


bool FTFont::MakeGlyphList()
{
    return true;
}


bool FTFont::CharMap( FT_Encoding encoding)
{
    bool result = face.CharMap( encoding);
    err = face.Error();
    return result;
}


float FTFont::Ascender() const
{
    return charSize.Ascender();
}


float FTFont::Descender() const
{
    return charSize.Descender();
}


void FTFont::BBox( const char* string,
                   float& llx, float& lly, float& llz, float& urx, float& ury, float& urz)
{
    llx = lly = llz = urx = ury = urz = 0.0f;
    
    if( !*string)
    {
        return;
    }
    
    const unsigned char* c = (unsigned char*)string;

    FTBBox bbox;
 
    while( *c)
    {
        CheckGlyph( *c);

        bbox = glyphList->BBox( *c);
        
        // Lower extent
        lly = lly < bbox.lowerY ? lly: bbox.lowerY;
        // Upper extent
        ury = ury > bbox.upperY ? ury: bbox.upperY;
        // Depth
        urz = urz < bbox.upperZ ? urz: bbox.upperZ;

        // Width
        urx += glyphList->Advance( *c, *(c + 1));
        ++c;
    }
    
    //Final adjustments
    llx = glyphList->BBox( *string).lowerX;
    urx -= glyphList->Advance( *(c - 1), 0);
    urx += bbox.upperX;

}

void FTFont::BBox( const wchar_t* string,
                   float& llx, float& lly, float& llz, float& urx, float& ury, float& urz)
{
    llx = lly = llz = urx = ury = urz = 0.0f;
    
    if( !*string)
    {
        return;
    }

    const wchar_t* c = string;
    FTBBox bbox;
 
    while( *c)
    {
        CheckGlyph( *c);

        bbox = glyphList->BBox( *c);
        
        // Lower extent
        lly = lly < bbox.lowerY ? lly: bbox.lowerY;
        // Upper extent
        ury = ury > bbox.upperY ? ury: bbox.upperY;
        // Depth
        urz = urz < bbox.upperZ ? urz: bbox.upperZ;

        // Width
        urx += glyphList->Advance( *c, *(c + 1));
        ++c;
    }
    
    //Final adjustments
    llx = glyphList->BBox( *string).lowerX;
    urx -= glyphList->Advance( *(c - 1), 0);
    urx += bbox.upperX;

}


float FTFont::Advance( const wchar_t* string)
{
    const wchar_t* c = string;
    float width = 0.0f;

    while( *c)
    {
        width += doAdvance( *c, *(c + 1));
        ++c;
    }

    return width;
}


float FTFont::Advance( const char* string)
{
    const unsigned char* c = (unsigned char*)string;
    float width = 0.0f;

    while( *c)
    {
        width += doAdvance( *c, *(c + 1));
        ++c;
    }

    return width;
}


float FTFont::doAdvance( const unsigned int chr, const unsigned int nextChr)
{
    CheckGlyph( chr);

    return glyphList->Advance( chr, nextChr);
}


void FTFont::Render( const char* string )
{
    const unsigned char* c = (unsigned char*)string;
    pen.x = 0; pen.y = 0;

    while( *c)
    {
        doRender( *c, *(c + 1));
        ++c;
    }
}


void FTFont::Render( const wchar_t* string )
{
    const wchar_t* c = string;
    pen.x = 0; pen.y = 0;

    while( *c)
    {
        doRender( *c, *(c + 1));
        ++c;
    }
}


void FTFont::doRender( const unsigned int chr, const unsigned int nextChr)
{
    CheckGlyph( chr);

    FTPoint kernAdvance = glyphList->Render( chr, nextChr, pen);
    
    pen.x += kernAdvance.x;
    pen.y += kernAdvance.y;
}


void FTFont::CheckGlyph( const unsigned int chr)
{
    if( !glyphList->Glyph( chr))
    {
        unsigned int g = face.CharIndex( chr);
        glyphList->Add( MakeGlyph( g), g);
    }
}

