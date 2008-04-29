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
 */

#include "config.h"

#include <cassert>
#include <string> // For memset

#include "FTInternals.h"

#include "FTGLTextureFont.h"
#include "FTGLTextureFontImpl.h"
#include "FTTextureGlyph.h"


//
//  FTGLTextureFont
//


FTGLTextureFont::FTGLTextureFont(char const *fontFilePath)
{
    impl = new FTGLTextureFontImpl(fontFilePath);
}


FTGLTextureFont::FTGLTextureFont(const unsigned char *pBufferBytes,
                                 size_t bufferSizeInBytes)
{
    impl = new FTGLTextureFontImpl(pBufferBytes, bufferSizeInBytes);
}


FTGLTextureFont::~FTGLTextureFont()
{
    ;
}


//
//  FTGLTextureFontImpl
//


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


FTGLTextureFontImpl::FTGLTextureFontImpl(const char* fontFilePath)
:   FTFontImpl(fontFilePath),
    maximumGLTextureSize(0),
    textureWidth(0),
    textureHeight(0),
    glyphHeight(0),
    glyphWidth(0),
    padding(3),
    xOffset(0),
    yOffset(0)
{
    remGlyphs = numGlyphs = face.GlyphCount();
}


FTGLTextureFontImpl::FTGLTextureFontImpl(const unsigned char *pBufferBytes,
                                         size_t bufferSizeInBytes)
:   FTFontImpl(pBufferBytes, bufferSizeInBytes),
    maximumGLTextureSize(0),
    textureWidth(0),
    textureHeight(0),
    glyphHeight(0),
    glyphWidth(0),
    padding(3),
    xOffset(0),
    yOffset(0)
{
    remGlyphs = numGlyphs = face.GlyphCount();
}


FTGLTextureFontImpl::~FTGLTextureFontImpl()
{
    glDeleteTextures(textureIDList.size(), (const GLuint*)&textureIDList[0]);
}


FTGlyph* FTGLTextureFontImpl::MakeGlyph(unsigned int glyphIndex)
{
    FT_GlyphSlot ftGlyph = face.Glyph(glyphIndex, FT_LOAD_NO_HINTING
                                                   | FT_LOAD_NO_BITMAP);

    if(ftGlyph)
    {
        glyphHeight = static_cast<int>(charSize.Height());
        glyphWidth = static_cast<int>(charSize.Width());

        if(textureIDList.empty())
        {
            textureIDList.push_back(CreateTexture());
            xOffset = yOffset = padding;
        }

        if(xOffset > (textureWidth - glyphWidth))
        {
            xOffset = padding;
            yOffset += glyphHeight;

            if(yOffset > (textureHeight - glyphHeight))
            {
                textureIDList.push_back(CreateTexture());
                yOffset = padding;
            }
        }

        FTTextureGlyph* tempGlyph = new FTTextureGlyph(ftGlyph, textureIDList[textureIDList.size() - 1],
                                                        xOffset, yOffset, textureWidth, textureHeight);
        xOffset += static_cast<int>(tempGlyph->BBox().upperX - tempGlyph->BBox().lowerX + padding);

        --remGlyphs;
        return tempGlyph;
    }

    err = face.Error();
    return NULL;
}


void FTGLTextureFontImpl::CalculateTextureSize()
{
    if(!maximumGLTextureSize)
    {
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, (GLint*)&maximumGLTextureSize);
        assert(maximumGLTextureSize); // If you hit this then you have an invalid OpenGL context.
    }

    textureWidth = NextPowerOf2((remGlyphs * glyphWidth) + (padding * 2));
    textureWidth = textureWidth > maximumGLTextureSize ? maximumGLTextureSize : textureWidth;

    int h = static_cast<int>((textureWidth - (padding * 2)) / glyphWidth);

    textureHeight = NextPowerOf2(((numGlyphs / h) + 1) * glyphHeight);
    textureHeight = textureHeight > maximumGLTextureSize ? maximumGLTextureSize : textureHeight;
}


GLuint FTGLTextureFontImpl::CreateTexture()
{
    CalculateTextureSize();

    int totalMemory = textureWidth * textureHeight;
    unsigned char* textureMemory = new unsigned char[totalMemory];
    memset(textureMemory, 0, totalMemory);

    GLuint textID;
    glGenTextures(1, (GLuint*)&textID);

    glBindTexture(GL_TEXTURE_2D, textID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, textureWidth, textureHeight,
                 0, GL_ALPHA, GL_UNSIGNED_BYTE, textureMemory);

    delete [] textureMemory;

    return textID;
}


bool FTGLTextureFontImpl::FaceSize(const unsigned int size, const unsigned int res)
{
    if(!textureIDList.empty())
    {
        glDeleteTextures(textureIDList.size(), (const GLuint*)&textureIDList[0]);
        textureIDList.clear();
        remGlyphs = numGlyphs = face.GlyphCount();
    }

    return FTFontImpl::FaceSize(size, res);
}


template <typename T>
inline void FTGLTextureFontImpl::RenderI(const T* string)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // GL_ONE

    FTTextureGlyph::ResetActiveTexture();

    FTFontImpl::Render(string);
}


void FTGLTextureFontImpl::Render(const char* string)
{
    RenderI(string);
}


void FTGLTextureFontImpl::Render(const char* string, int renderMode)
{
    RenderI(string);
}


void FTGLTextureFontImpl::Render(const wchar_t* string)
{
    RenderI(string);
}


void FTGLTextureFontImpl::Render(const wchar_t* string, int renderMode)
{
    RenderI(string);
}

