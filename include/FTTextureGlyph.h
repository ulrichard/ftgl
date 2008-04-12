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

#ifndef     __FTTextureGlyph__
#define     __FTTextureGlyph__


#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTGL.h"
#include "FTGlyph.h"


/**
 * FTTextureGlyph is a specialisation of FTGlyph for creating texture
 * glyphs.
 * 
 * @see FTGlyphContainer
 *
 */
class FTGL_EXPORT FTTextureGlyph : public FTGlyph
{
    public:
        /**
         * Constructor
         *
         * @param glyph     The Freetype glyph to be processed
         * @param id        The id of the texture that this glyph will be
         *                  drawn in
         * @param xOffset   The x offset into the parent texture to draw
         *                  this glyph
         * @param yOffset   The y offset into the parent texture to draw
         *                  this glyph
         * @param width     The width of the parent texture
         * @param height    The height (number of rows) of the parent texture
         */
        FTTextureGlyph( FT_GlyphSlot glyph, int id, int xOffset, int yOffset, GLsizei width, GLsizei height);

        /**
         * Destructor
         */
        virtual ~FTTextureGlyph();

        /**
         * Renders this glyph at the current pen position.
         *
         * @param pen   The current pen position.
         * @return      The advance distance for this glyph.
         */
        virtual const FTPoint& Render( const FTPoint& pen);
        
        /**
         * Reset the currently active texture to zero to get into a known state before
         * drawing a string. This is to get round possible threading issues.
         */
        static void ResetActiveTexture(){ activeTextureID = 0;}
        
    private:
        /**
         * The width of the glyph 'image'
         */
        int destWidth;

        /**
         * The height of the glyph 'image'
         */
        int destHeight;

        /**
         * Vector from the pen position to the topleft corner of the pixmap
         */
        FTPoint pos;
        
        /**
         * The texture co-ords of this glyph within the texture.
         */
        FTPoint uv[2];
        
        /**
         * The texture index that this glyph is contained in.
         */
        int glTextureID;

        /**
         * The texture index of the currently active texture
         *
         * We keep track of the currently active texture to try to reduce the number
         * of texture bind operations.
         */
        static GLint activeTextureID;
        
};


#endif  //  __FTTextureGlyph__
