#include    "FTFace.h"
#include    "FTFont.h"
#include    "FTGlyphContainer.h"
#include    "FTBBox.h"


FTFont::FTFont( const char* fontname)
:   face( fontname),
    glyphList(0)
{
    err = face.Error();
}


FTFont::FTFont( const unsigned char *pBufferBytes, size_t bufferSizeInBytes)
:   face( pBufferBytes, bufferSizeInBytes),
    glyphList(0)
{
    err = face.Error();
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


bool FTFont::Attach( const unsigned char *pBufferBytes, size_t bufferSizeInBytes)
{
    if( face.Attach( pBufferBytes, bufferSizeInBytes))
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
    return true;
}


unsigned int FTFont::FaceSize() const
{
    return charSize.CharSize();
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

void FTFont::BBox(const char *String,const int StartIdx,const int EndIdx,
                  float& llx, float& lly, float& llz, float& urx, float& ury, float& urz) {
    FTBBox totalBBox;

    if (String && ('\0' != String[StartIdx])) {
        CheckGlyph(String[StartIdx]);

        totalBBox = glyphList->BBox(String[StartIdx]);
        float advance = glyphList->Advance(String[StartIdx],String[StartIdx + 1]);
            
        for (int idx = StartIdx + 1;((EndIdx < 0) && String[idx]) || ((EndIdx >= 0) && (idx <= EndIdx));idx++) {
            CheckGlyph(String[idx]);
            FTBBox tempBBox = glyphList->BBox(String[idx]);
            tempBBox.Move(FTPoint(advance,0.0f,0.0f));

            totalBBox += tempBBox;
            advance += glyphList->Advance(String[idx],String[idx + 1]);
        } /* Expand totalBox by each glyph in String (for idx) */
    } /* Only compute the bounds if String is non-empty (if String) */

    // TODO: The Z values do not follow the proper ordering.  I'm not sure why.
    llx = totalBBox.lowerX < totalBBox.upperX ? totalBBox.lowerX : totalBBox.upperX;
    lly = totalBBox.lowerY < totalBBox.upperY ? totalBBox.lowerY : totalBBox.upperY;
    llz = totalBBox.lowerZ < totalBBox.upperZ ? totalBBox.lowerZ : totalBBox.upperZ;
    urx = totalBBox.lowerX > totalBBox.upperX ? totalBBox.lowerX : totalBBox.upperX;
    ury = totalBBox.lowerY > totalBBox.upperY ? totalBBox.lowerY : totalBBox.upperY;
    urz = totalBBox.lowerZ > totalBBox.upperZ ? totalBBox.lowerZ : totalBBox.upperZ;
} /* FTFont::BBox() */

void FTFont::BBox(const wchar_t *String,const int StartIdx,const int EndIdx,
                  float& llx, float& lly, float& llz, float& urx, float& ury, float& urz) {
    FTBBox totalBBox;

    if (String && ('\0' != String[StartIdx])) {
        CheckGlyph(String[StartIdx]);

        totalBBox = glyphList->BBox(String[StartIdx]);
        float advance = glyphList->Advance(String[StartIdx],String[StartIdx + 1]);
            
        for (int idx = StartIdx + 1;((EndIdx < 0) && String[idx]) || ((EndIdx >= 0) && (idx <= EndIdx));idx++) {
            CheckGlyph(String[idx]);
            FTBBox tempBBox = glyphList->BBox(String[idx]);
            tempBBox.Move(FTPoint(advance,0.0f,0.0f));

            totalBBox += tempBBox;
            advance += glyphList->Advance(String[idx],String[idx + 1]);
        } /* Expand totalBox by each glyph in String (for idx) */
    } /* Only compute the bounds if String is non-empty (if String) */

    // TODO: The Z values do not follow the proper ordering.  I'm not sure why.
    llx = totalBBox.lowerX < totalBBox.upperX ? totalBBox.lowerX : totalBBox.upperX;
    lly = totalBBox.lowerY < totalBBox.upperY ? totalBBox.lowerY : totalBBox.upperY;
    llz = totalBBox.lowerZ < totalBBox.upperZ ? totalBBox.lowerZ : totalBBox.upperZ;
    urx = totalBBox.lowerX > totalBBox.upperX ? totalBBox.lowerX : totalBBox.upperX;
    ury = totalBBox.lowerY > totalBBox.upperY ? totalBBox.lowerY : totalBBox.upperY;
    urz = totalBBox.lowerZ > totalBBox.upperZ ? totalBBox.lowerZ : totalBBox.upperZ;
} /* FTFont::BBox() */

float FTFont::Advance( const wchar_t* string)
{
    const wchar_t* c = string;
    float width = 0.0f;

    while( *c)
    {
        CheckGlyph( *c);
        width += glyphList->Advance( *c, *(c + 1));
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
        CheckGlyph( *c);
        width += glyphList->Advance( *c, *(c + 1));
        ++c;
    }
    
    return width;
}

void FTFont::Render( const char* string )
{
    const unsigned char* c = (unsigned char*)string;
    pen.x = 0; pen.y = 0;

    while( *c)
    {
        DoRender( *c, *(c + 1),pen);
        ++c;
    }
}


void FTFont::Render( const wchar_t* string )
{
    const wchar_t* c = string;
    pen.x = 0; pen.y = 0;

    while( *c)
    {
        DoRender( *c, *(c + 1),pen);
        ++c;
    }
}


void FTFont::DoRender( const unsigned int chr, const unsigned int nextChr, FTPoint &origin)
{
    CheckGlyph( chr);

    FTPoint kernAdvance = glyphList->Render( chr, nextChr, origin);
    
    origin.x += kernAdvance.x;
    origin.y += kernAdvance.y;
}


void FTFont::CheckGlyph( const unsigned int chr)
{
    if( !glyphList->Glyph( chr))
    {
        unsigned int g = face.CharIndex( chr);
        glyphList->Add( MakeGlyph( g), g);
    }
}

