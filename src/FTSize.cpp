#include    "FTSize.h"


FTSize::FTSize()
:   ftFace(0),
    size(0),
    err(0)
{}


FTSize::~FTSize()
{}


bool FTSize::CharSize( FT_Face* face, unsigned int point_size, unsigned int x_resolution, unsigned int y_resolution )
{
    ftFace = face;
    size = point_size;
    err = FT_Set_Char_Size( *ftFace, 0L, point_size * 64, x_resolution, y_resolution);
    
    ftSize = (*ftFace)->size;
    
    return !err;
}


unsigned int FTSize::CharSize() const
{
    return size;
}


int FTSize::Ascender() const
{
    return ftSize->metrics.ascender >> 6;
}


int FTSize::Descender() const
{
    return ftSize->metrics.descender >> 6;
}


int FTSize::Height() const
{
    if( FT_IS_SCALABLE((*ftFace)))
    {
        float height = ( (*ftFace)->bbox.yMax - (*ftFace)->bbox.yMin)
                     * ( (float)ftSize->metrics.y_ppem / (float)(*ftFace)->units_per_EM);
                     
        return static_cast<int>(height);
    }
    else
    {
        return ftSize->metrics.height >> 6;
    }
}


int FTSize::Width() const
{
    if( FT_IS_SCALABLE((*ftFace)))
    {
        float width = ( (*ftFace)->bbox.xMax - (*ftFace)->bbox.xMin)
                    * ( (float)ftSize->metrics.x_ppem / (float)(*ftFace)->units_per_EM);
                    
        return static_cast<int>(width);
    }
    else
    {
        return ftSize->metrics.max_advance >> 6;
    }
}


int FTSize::Underline() const
{
    return 0;
}
