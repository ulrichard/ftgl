#include    "FTGLExtrdFont.h"
#include    "FTExtrdGlyph.h"


FTGLExtrdFont::FTGLExtrdFont()
:   depth(0.0f)
{}


FTGLExtrdFont::~FTGLExtrdFont()
{}


FTGlyph* FTGLExtrdFont::MakeGlyph( unsigned int g)
{
    FT_Glyph* ftGlyph = face.Glyph( g, FT_LOAD_DEFAULT);

    if( ftGlyph)
    {
        FTExtrdGlyph* tempGlyph = new FTExtrdGlyph( *ftGlyph, depth);
        return tempGlyph;
    }

    err = face.Error();
    return NULL;
}


