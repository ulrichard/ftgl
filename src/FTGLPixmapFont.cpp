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

#include "FTGLPixmapFont.h"
#include "FTPixmapGlyph.h"


//
//  FTGLPixmapFont
//


FTGLPixmapFont::FTGLPixmapFont(char const *fontFilePath) :
    FTFont(FTGL::FONT_PIXMAP, fontFilePath)
{
    ;
}


FTGLPixmapFont::FTGLPixmapFont(const unsigned char *pBufferBytes,
                               size_t bufferSizeInBytes) :
    FTFont(FTGL::FONT_PIXMAP, pBufferBytes, bufferSizeInBytes)
{
    ;
}


FTGLPixmapFont::~FTGLPixmapFont()
{
    ;
}


//
//  FTGLPixmapFontImpl
//


FTGLPixmapFontImpl::FTGLPixmapFontImpl(const char* fontFilePath)
:   FTFontImpl(fontFilePath)
{
    ;
}


FTGLPixmapFontImpl::FTGLPixmapFontImpl(const unsigned char *pBufferBytes,
                                       size_t bufferSizeInBytes)
:   FTFontImpl(pBufferBytes, bufferSizeInBytes)
{
    ;
}


FTGLPixmapFontImpl::~FTGLPixmapFontImpl()
{
    ;
}


FTGlyph* FTGLPixmapFontImpl::MakeGlyph(unsigned int g)
{
    FT_GlyphSlot ftGlyph = face.Glyph(g, FT_LOAD_NO_HINTING
                                          | FT_LOAD_NO_BITMAP);

    if(ftGlyph)
    {
        FTPixmapGlyph* tempGlyph = new FTPixmapGlyph(ftGlyph);
        return tempGlyph;
    }

    err = face.Error();
    return NULL;
}


template <typename T>
inline void FTGLPixmapFontImpl::RenderI(const T* string)
{
    glPushAttrib(GL_ENABLE_BIT | GL_PIXEL_MODE_BIT | GL_COLOR_BUFFER_BIT);
    glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_TEXTURE_2D);

    GLfloat ftglColour[4];
    glGetFloatv(GL_CURRENT_RASTER_COLOR, ftglColour);

    glPixelTransferf(GL_RED_SCALE, ftglColour[0]);
    glPixelTransferf(GL_GREEN_SCALE, ftglColour[1]);
    glPixelTransferf(GL_BLUE_SCALE, ftglColour[2]);
    glPixelTransferf(GL_ALPHA_SCALE, ftglColour[3]);

    FTFontImpl::Render(string);

    glPopClientAttrib();
    glPopAttrib();
}


void FTGLPixmapFontImpl::Render(const char* string)
{
    RenderI(string);
}


void FTGLPixmapFontImpl::Render(const wchar_t* string)
{
    RenderI(string);
}


namespace C
{
    extern "C" FTGLfont* ftglCreatePixmapFont(const char *fontname)
    {
        FTGLfont *ftgl = createFTFont(Pixmap, fontname);
        return ftgl;
    }
}

