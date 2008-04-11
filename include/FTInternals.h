#include    "FTFont.h"
#include    "FTGLBitmapFont.h"
#include    "FTGLPixmapFont.h"
#include    "FTGLOutlineFont.h"
#include    "FTGLPolygonFont.h"
#include    "FTGLExtrdFont.h"
#include    "FTGLTextureFont.h"
#include    <stdlib.h>
#include    <stdio.h>

#ifndef __FTINTERNALS_H__
#define __FTINTERNALS_H__

#ifdef __cplusplus
extern "C" {
namespace C {
#endif

typedef enum ftglType
{
    Bitmap,
    Pixmap,
    Outline,
    Polygon,
    Extrude,
    Texture,
};

struct FTGLfont
{
    FTFont *ptr;
    ftglType type;
};

static inline FTGLfont *createFTFont(ftglType type, const char *fontname)
{
    FTGLfont *ftgl = (FTGLfont*)malloc(sizeof(FTGLfont));
    ftgl->type = type;
    switch(type)
    {
        case Bitmap:
            ftgl->ptr = new FTGLBitmapFont(fontname);
            break;
        case Pixmap:
            ftgl->ptr = new FTGLPixmapFont(fontname);
            break;
        case Outline:
            ftgl->ptr = new FTGLOutlineFont(fontname);
            break;
        case Polygon:
            ftgl->ptr = new FTGLPolygonFont(fontname);
            break;
        case Extrude:
            ftgl->ptr = new FTGLExtrdFont(fontname);
            break;
        case Texture:
            ftgl->ptr = new FTGLTextureFont(fontname);
            break;
    }
    return ftgl;
}

#ifdef __cplusplus
}
}
#endif

#endif  //__FTINTERNALS_H__

