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

#ifndef     __FTGLTextureFont__
#define     __FTGLTextureFont__

#ifdef __cplusplus

#include "FTFont.h"
#include "FTVector.h"
#include "FTGL.h"

class FTTextureGlyph;
class FTFontImpl;


/**
 * FTGLTextureFont is a specialisation of the FTFont class for handling
 * Texture mapped fonts
 *
 * @see     FTFont
 */
class  FTGL_EXPORT FTGLTextureFont : public FTFont
{
    public:
        /**
         * Open and read a font file. Sets Error flag.
         *
         * @param fontFilePath  font file path.
         */
        FTGLTextureFont(const char* fontFilePath);

        /**
         * Open and read a font from a buffer in memory. Sets Error flag.
         *
         * @param pBufferBytes  the in-memory buffer
         * @param bufferSizeInBytes  the length of the buffer in bytes
         */
        FTGLTextureFont(const unsigned char *pBufferBytes,
                        size_t bufferSizeInBytes);

        /**
         * Destructor
         */
        virtual ~FTGLTextureFont();
};


class FTGLTextureFontImpl : public FTFontImpl
{
    friend class FTGLTextureFont;

    public:
        FTGLTextureFontImpl(const char* fontFilePath);

        FTGLTextureFontImpl(const unsigned char *pBufferBytes,
                            size_t bufferSizeInBytes);

        ~FTGLTextureFontImpl();

        /**
         * Set the char size for the current face.
         *
         * @param size      the face size in points (1/72 inch)
         * @param res       the resolution of the target device.
         * @return          <code>true</code> if size was set correctly
         */
        virtual bool FaceSize(const unsigned int size,
                              const unsigned int res = 72);

        /**
         * Renders a string of characters
         *
         * @param string    'C' style string to be output.
         */
        virtual void Render(const char* string);

        /**
         * Render a string of characters
         *
         * @param string    'C' style string to be output.
         * @param renderMode    Render mode to display
         */
        void Render(const char* string, int renderMode) { Render(string); }

        /**
         * Renders a string of characters
         *
         * @param string    wchar_t string to be output.
         */
        virtual void Render(const wchar_t* string);

        /**
         * Render a string of characters
         *
         * @param string    wchar_t string to be output.
         * @param renderMode    Render mode to display
         */
        void Render(const wchar_t *string, int renderMode) { Render(string); }

    private:
        /**
         * Construct a FTTextureGlyph.
         *
         * @param glyphIndex The glyph index NOT the char code.
         * @return  An FTTextureGlyph or <code>null</code> on failure.
         */
        inline virtual FTGlyph* MakeGlyph(unsigned int glyphIndex);

        /**
         * Get the size of a block of memory required to layout the glyphs
         *
         * Calculates a width and height based on the glyph sizes and the
         * number of glyphs. It over estimates.
         */
        inline void CalculateTextureSize();

        /**
         * Creates a 'blank' OpenGL texture object.
         *
         * The format is GL_ALPHA and the params are
         * GL_TEXTURE_WRAP_S = GL_CLAMP
         * GL_TEXTURE_WRAP_T = GL_CLAMP
         * GL_TEXTURE_MAG_FILTER = GL_LINEAR
         * GL_TEXTURE_MIN_FILTER = GL_LINEAR
         * Note that mipmapping is NOT used
         */
        inline GLuint CreateTexture();

        /**
         * The maximum texture dimension on this OpenGL implemetation
         */
        GLsizei maximumGLTextureSize;

        /**
         * The minimum texture width required to hold the glyphs
         */
        GLsizei textureWidth;

        /**
         * The minimum texture height required to hold the glyphs
         */
        GLsizei textureHeight;

        /**
         *An array of texture ids
         */
         FTVector<GLuint> textureIDList;

        /**
         * The max height for glyphs in the current font
         */
        int glyphHeight;

        /**
         * The max width for glyphs in the current font
         */
        int glyphWidth;

        /**
         * A value to be added to the height and width to ensure that
         * glyphs don't overlap in the texture
         */
        unsigned int padding;

        /**
         *
         */
         unsigned int numGlyphs;

        /**
         */
        unsigned int remGlyphs;

        /**
         */
        int xOffset;

        /**
         */
        int yOffset;

        /* Internal generic Render() implementation */
        template <typename T>
        inline void RenderI(const T* string);
};

#endif //__cplusplus

#ifdef __cplusplus
extern "C" {
namespace C {
#endif
FTGL_EXPORT FTGLfont *ftglCreateTextureFont(const char *fontname);
#ifdef __cplusplus
}
}
#endif

#endif // __FTGLTextureFont__



