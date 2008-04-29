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

#ifndef __FTGlyph__
#define __FTGlyph__

#include <ftgl.h>

class FTGlyphImpl;

/**
 * FTGlyph is the base class for FTGL glyphs.
 *
 * It provides the interface between Freetype glyphs and their openGL
 * renderable counterparts. This is an abstract class and derived classes
 * must implement the <code>render</code> function.
 *
 * @see FTGlyphContainer
 * @see FTBBox
 * @see FTPoint
 *
 */
class FTGL_EXPORT FTGlyph
{
    friend class FTGlyphContainer;

    protected:
        FTGlyph();
        virtual ~FTGlyph();

    public:
        /**
         * Renders this glyph at the current pen position.
         *
         * @param pen   The current pen position.
         * @param renderMode Render mode to display
         * @return      The advance distance for this glyph.
         */
        const FTPoint& Render(const FTPoint& pen, int renderMode);

        /**
         * Return the advance width for this glyph.
         *
         * @return  advance width.
         */
        const FTPoint& Advance() const;

        /**
         * Return the bounding box for this glyph.
         *
         * @return  bounding box.
         */
        const FTBBox& BBox() const;

        /**
         * Queries for errors.
         *
         * @return  The current error code.
         */
        FT_Error Error() const;

    protected:
        FTGlyphImpl *impl;
};

#endif  //  __FTGlyph__

