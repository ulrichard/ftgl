#ifndef     __FTBBox__
#define     __FTBBox__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTGL.h"


/**
 * FTBBox
 *
 *
 */
class FTGL_EXPORT FTBBox
{
    public:
        FTBBox()
        :   lowerX(0),
            lowerY(0),
            lowerZ(0),
            upperX(0),
            upperY(0),
            upperZ(0)
        {}
        
        FTBBox( FT_Glyph glyph)
        {
            FT_BBox bbox;
            FT_Glyph_Get_CBox( glyph, ft_glyph_bbox_subpixels, &bbox );
            
            lowerX = bbox.xMin >> 6;
            lowerY = bbox.yMin >> 6;
            lowerZ = 0;
            upperX = bbox.xMax >> 6;
            upperY = bbox.yMax >> 6;
            upperZ = 0; 
        }       
        
        FTBBox( int a, int b, int c, int d, int e, int f)
        :   lowerX(a),
            lowerY(b),
            lowerZ(c),
            upperX(d),
            upperY(e),
            upperZ(f)
        {}

        ~FTBBox()
        {}
        
        // Make these ftPoints & private
        float lowerX, lowerY, lowerZ, upperX, upperY, upperZ;
    protected:
    
    
    private:

};


#endif  //  __FTBBox__

