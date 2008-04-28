/*
 * FTGL - OpenGL font library
 *
 * Copyright (c) 2001-2004 Henry Maddocks <ftgl@opengl.geek.nz>
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

#include "config.h"

#include "FTInternals.h"

#include "FTGLPolygonFont.h"
#include "FTGLPolygonFontImpl.h"
#include "FTPolyGlyph.h"


//
//  FTGLPolygonFont
//


FTGLPolygonFont::FTGLPolygonFont(char const *fontFilePath) :
    FTFont(FTGL::FONT_POLYGON, fontFilePath)
{
    ;
}


FTGLPolygonFont::FTGLPolygonFont(const unsigned char *pBufferBytes,
                                 size_t bufferSizeInBytes) :
    FTFont(FTGL::FONT_POLYGON, pBufferBytes, bufferSizeInBytes)
{
    ;
}


FTGLPolygonFont::~FTGLPolygonFont()
{
    ;
}


//
//  FTGLPolygonFontImpl
//


FTGLPolygonFontImpl::FTGLPolygonFontImpl(const char* fontFilePath)
:   FTFontImpl(fontFilePath),
    outset(0.0f)
{
    ;
}


FTGLPolygonFontImpl::FTGLPolygonFontImpl(const unsigned char *pBufferBytes,
                                         size_t bufferSizeInBytes)
:   FTFontImpl(pBufferBytes, bufferSizeInBytes)
{
    ;
}


FTGLPolygonFontImpl::~FTGLPolygonFontImpl()
{
    ;
}


FTGlyph* FTGLPolygonFontImpl::MakeGlyph(unsigned int g)
{
    FT_GlyphSlot ftGlyph = face.Glyph(g, FT_LOAD_NO_HINTING);

    if(ftGlyph)
    {
        FTPolyGlyph* tempGlyph = new FTPolyGlyph(ftGlyph, outset, useDisplayLists);
        return tempGlyph;
    }

    err = face.Error();
    return NULL;
}


namespace C
{
    extern "C" FTGLfont* ftglCreatePolygonFont(const char *fontname)
    {
        FTGLfont *ftgl = createFTFont(Polygon, fontname);
        return ftgl;
    }
}

