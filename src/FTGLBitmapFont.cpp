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

#include "FTGLBitmapFont.h"
#include "FTGLBitmapFontImpl.h"
#include "FTBitmapGlyph.h"


//
//  FTGLBitmapFont
//


FTGLBitmapFont::FTGLBitmapFont(char const *fontFilePath) :
    FTFont(FTGL::FONT_BITMAP, fontFilePath)
{
    ;
}


FTGLBitmapFont::FTGLBitmapFont(unsigned char const *pBufferBytes,
                               size_t bufferSizeInBytes) :
    FTFont(FTGL::FONT_BITMAP, pBufferBytes, bufferSizeInBytes)
{
    ;
}


FTGLBitmapFont::~FTGLBitmapFont()
{
    ;
}


//
//  FTGLBitmapFontImpl
//


FTGLBitmapFontImpl::FTGLBitmapFontImpl(char const* fontFilePath)
:   FTFontImpl(fontFilePath)
{}


FTGLBitmapFontImpl::FTGLBitmapFontImpl(unsigned char const *pBufferBytes,
                                       size_t bufferSizeInBytes)
:   FTFontImpl(pBufferBytes, bufferSizeInBytes)
{}


FTGLBitmapFontImpl::~FTGLBitmapFontImpl()
{}


FTGlyph* FTGLBitmapFontImpl::MakeGlyph(unsigned int g)
{
    FT_GlyphSlot ftGlyph = face.Glyph(g, FT_LOAD_DEFAULT);

    if(ftGlyph)
    {
        FTBitmapGlyph* tempGlyph = new FTBitmapGlyph(ftGlyph);
        return tempGlyph;
    }

    err = face.Error();
    return NULL;
}


template <typename T>
inline void FTGLBitmapFontImpl::RenderI(const T *string)
{
    glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);
    glPushAttrib(GL_ENABLE_BIT);

    glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glDisable(GL_BLEND);

    FTFontImpl::Render(string);

    glPopAttrib();
    glPopClientAttrib();
}


void FTGLBitmapFontImpl::Render(const char* string)
{
    RenderI(string);
}


void FTGLBitmapFontImpl::Render(const wchar_t* string)
{
    RenderI(string);
}


/* FIXME: is this needed? */
void FTGLBitmapFont::Render(const char* string)
{
    impl->Render(string);
}


void FTGLBitmapFont::Render(const wchar_t* string)
{
    impl->Render(string);
}


namespace C
{
    extern "C" FTGLfont* ftglCreateBitmapFont(const char *fontname)
    {
        FTGLfont *ftgl = createFTFont(Bitmap, fontname);
        return ftgl;
    }
}

