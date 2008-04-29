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

#ifndef     __FTBitmapGlyph__
#define     __FTBitmapGlyph__


#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "ftgl.h"
#include "FTGlyph.h"


/**
 * FTBitmapGlyph is a specialisation of FTGlyph for creating bitmaps.
 *
 * It provides the interface between Freetype glyphs and their openGL
 * Renderable counterparts. This is an abstract class and derived classes
 * must implement the <code>Render</code> function.
 *
 * @see FTGlyphContainer
 *
 */
class FTGL_EXPORT FTBitmapGlyph : public FTGlyph
{
    public:
        /**
         * Constructor
         *
         * @param glyph The Freetype glyph to be processed
         */
        FTBitmapGlyph(FT_GlyphSlot glyph);

        /**
         * Destructor
         */
        virtual ~FTBitmapGlyph();

        /**
         * Renders this glyph at the current pen position.
         *
         * @param pen   The current pen position.
         * @param renderMode    Render mode to display
         * @return      The advance distance for this glyph.
         */
        virtual const FTPoint& Render(const FTPoint& pen, int renderMode);

    private:
        /**
         * The width of the glyph 'image'
         */
        unsigned int destWidth;

        /**
         * The height of the glyph 'image'
         */
        unsigned int destHeight;

        /**
         * The pitch of the glyph 'image'
         */
        unsigned int destPitch;

        /**
         * Vector from the pen position to the topleft corner of the bitmap
         */
        FTPoint pos;

        /**
         * Pointer to the 'image' data
         */
        unsigned char* data;

};


#endif  //  __FTBitmapGlyph__

