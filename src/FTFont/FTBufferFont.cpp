/*
 * FTGL - OpenGL font library
 *
 * Copyright (c) 2008 Sam Hocevar <sam@zoy.org>
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
 */

#include "config.h"

#include "FTGL/ftgl.h"

#include "FTInternals.h"
#include "FTBufferFontImpl.h"


//
//  FTBufferFont
//


FTBufferFont::FTBufferFont(char const *fontFilePath) :
    FTFont(new FTBufferFontImpl(this, fontFilePath))
{}


FTBufferFont::FTBufferFont(unsigned char const *pBufferBytes,
                           size_t bufferSizeInBytes) :
    FTFont(new FTBufferFontImpl(this, pBufferBytes, bufferSizeInBytes))
{}


FTBufferFont::~FTBufferFont()
{}


FTGlyph* FTBufferFont::MakeGlyph(FT_GlyphSlot ftGlyph)
{
    FTBufferFontImpl *myimpl = dynamic_cast<FTBufferFontImpl *>(impl);
    if(!myimpl)
    {
        return NULL;
    }

    return myimpl->MakeGlyphImpl(ftGlyph);
}


//
//  FTBufferFontImpl
//


FTBufferFontImpl::FTBufferFontImpl(FTFont *ftFont, const char* fontFilePath) :
    FTFontImpl(ftFont, fontFilePath),
    buffer(new FTBuffer())
{
    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


FTBufferFontImpl::FTBufferFontImpl(FTFont *ftFont,
                                   const unsigned char *pBufferBytes,
                                   size_t bufferSizeInBytes) :
    FTFontImpl(ftFont, pBufferBytes, bufferSizeInBytes),
    buffer(new FTBuffer())
{
    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


FTBufferFontImpl::~FTBufferFontImpl()
{
    glDeleteTextures(1, &id);

    if(buffer->pixels)
        delete[] buffer->pixels;

    delete buffer;
}


FTGlyph* FTBufferFontImpl::MakeGlyphImpl(FT_GlyphSlot ftGlyph)
{
    return new FTBufferGlyph(ftGlyph, buffer);
}


static inline GLuint NextPowerOf2(GLuint in)
{
     in -= 1;

     in |= in >> 16;
     in |= in >> 8;
     in |= in >> 4;
     in |= in >> 2;
     in |= in >> 1;

     return in + 1;
}


template <typename T>
inline FTPoint FTBufferFontImpl::RenderI(const T* string, const int len,
                                         FTPoint position, FTPoint spacing,
                                         int renderMode)
{
    const float border = 1.0f;

    FTBBox bbox = BBox(string, len, position, spacing);

    int width = static_cast<int>(bbox.Upper().X() - bbox.Lower().X()
                                  + border + border + 0.5);
    int height = static_cast<int>(bbox.Upper().Y() - bbox.Lower().Y()
                                   + border + border + 0.5);

    int texWidth = NextPowerOf2(width);
    int texHeight = NextPowerOf2(height);

    if(buffer->pixels)
    {
        delete[] buffer->pixels;
    }
    buffer->pixels = new unsigned char[texWidth * texHeight];
    memset(buffer->pixels, 0, texWidth * texHeight);
    buffer->width = texWidth;
    buffer->height = texHeight;
    buffer->pitch = texWidth;
    buffer->pos = FTPoint(1, 1) - bbox.Lower();

    FTPoint tmp = FTFontImpl::Render(string, len, position,
                                     spacing, renderMode);

    // Protect blending functions, GL_BLEND and GL_TEXTURE_2D
    glPushAttrib(GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT);

    // Protect glPixelStorei() calls
    glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // GL_ONE

    glBindTexture(GL_TEXTURE_2D, id);

    glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    /* TODO: use glTexSubImage2D later? */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, texWidth, texHeight, 0,
                 GL_ALPHA, GL_UNSIGNED_BYTE, (GLvoid *)buffer->pixels);

    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(border / texWidth,
                     (texHeight - height + border) / texHeight);
        glVertex2f(bbox.Lower().Xf(), bbox.Upper().Yf());
        glTexCoord2f(border / texWidth,
                     (texHeight - border) / texHeight);
        glVertex2f(bbox.Lower().Xf(), bbox.Lower().Yf());
        glTexCoord2f((width - border) / texWidth,
                     (texHeight - border) / texHeight);
        glVertex2f(bbox.Upper().Xf(), bbox.Lower().Yf());
        glTexCoord2f((width - border) / texWidth,
                     (texHeight - height + border) / texHeight);
        glVertex2f(bbox.Upper().Xf(), bbox.Upper().Yf());
    glEnd();

    glPopClientAttrib();
    glPopAttrib();

    return tmp;
}


FTPoint FTBufferFontImpl::Render(const char * string, const int len,
                                 FTPoint position, FTPoint spacing,
                                 int renderMode)
{
    return RenderI(string, len, position, spacing, renderMode);
}


FTPoint FTBufferFontImpl::Render(const wchar_t * string, const int len,
                                 FTPoint position, FTPoint spacing,
                                 int renderMode)
{
    return RenderI(string, len, position, spacing, renderMode);
}

