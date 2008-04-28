/*
 * FTGL - OpenGL font library
 *
 * Copyright (c) 2001-2004 Henry Maddocks <ftgl@opengl.geek.nz>
 *               2008 Éric Beets <ericbeets@free.fr>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Alternatively, you can redistribute and/or modify this software under
 * the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License,
 * or (at your option) any later version.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA.
 */

#include    "FTFont.h"
#include    "FTGLBitmapFont.h"
#include    "FTGLPixmapFont.h"
#include    "FTGLOutlineFont.h"
#include    "FTGLPolygonFont.h"
#include    "FTGLExtrdFont.h"
#include    "FTGLTextureFont.h"

#include    "FTLayout.h"
#include    "FTSimpleLayout.h"

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

    if(ftgl->ptr->Error())
    {
        delete ftgl->ptr;
        free(ftgl);
        return NULL;
    }

    return ftgl;
}

typedef enum ftglLayoutType
{
    Simple,
};

struct FTGLlayout
{
    FTLayout *ptr;
    FTGLfont *font;
    ftglLayoutType type;
};

static inline FTGLlayout *createFTLayout(ftglLayoutType type)
{
    FTGLlayout *layout = (FTGLlayout*)malloc(sizeof(FTGLlayout));
    layout->font = NULL;
    layout->type = type;
    switch(type)
    {
        case Simple:
            layout->ptr = new FTSimpleLayout();
            break;
    }
    return layout;
}

#ifdef __cplusplus
}
}
#endif

#endif  //__FTINTERNALS_H__

