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

#ifndef    __FTLayout__
#define    __FTLayout__

#include "FTGL.h"
#include "FTPoint.h"
#include "FTFont.h"

/**
 * FTLayout is the interface for layout managers that render text.
 *
 * Specific layout manager classes are derived from this class. This class
 * is abstract and deriving classes must implement the protected
 * <code>Render</code> methods to render formatted text and
 * <code>BBox</code> methods to determine the bounding box of output text.
 *
 * @see     FTFont
 */
class FTGL_EXPORT FTLayout
{
    public:
        /**
         * Get the bounding box for a formatted string.
         *
         * @param string    a char string
         * @param llx       lower left near x coord
         * @param lly       lower left near y coord
         * @param llz       lower left near z coord
         * @param urx       upper right far x coord
         * @param ury       upper right far y coord
         * @param urz       upper right far z coord
         */
        virtual void BBox(const char* string, float& llx, float& lly,
                          float& llz, float& urx, float& ury, float& urz) = 0;

        /**
         * Get the bounding box for a formatted string.
         *
         * @param string    a wchar_t string
         * @param llx       lower left near x coord
         * @param lly       lower left near y coord
         * @param llz       lower left near z coord
         * @param urx       upper right far x coord
         * @param ury       upper right far y coord
         * @param urz       upper right far z coord
         */
        virtual void BBox(const wchar_t* string, float& llx, float& lly,
                          float& llz, float& urx, float& ury, float& urz) = 0;

        /**
         * Render a string of characters
         *
         * @param string    'C' style string to be output.
         */
        virtual void Render(const char *string) = 0;

        /**
         * Render a string of characters
         *
         * @param string    wchar_t string to be output.
         */
        virtual void Render(const wchar_t *string) = 0;

    protected:
        /**
         * Current pen or cursor position;
         */
        FTPoint pen;

        /**
         * Expose <code>FTFont::DoRender</code> method to derived classes.
         *
         * @param font      The font that contains the glyph.
         * @param chr       current character
         * @param nextChr   next character
         * @see FTFont::DoRender
         */
        void DoRender(FTFont *font, const unsigned int chr,
                      const unsigned int nextChr)
            { font->DoRender(chr, nextChr, pen); }

        /**
         * Expose <code>FTFont::CheckGlyph</code> method to derived classes.
         *
         * @param font The font that contains the glyph.
         * @param chr  character index
         */
        void CheckGlyph(FTFont *font, const unsigned int Chr)
            { font->CheckGlyph(Chr); }

         /**
          * Expose the FTFont <code>glyphList</code> to our derived classes.
          *
          * @param font The font to perform the query on.
          * @param Char The character corresponding to the glyph to query.
          *
          * @return A pointer to the glyphList of font.
          */
         FTGlyphContainer *GetGlyphs(FTFont *font)
            { return(font->glyphList); }

         /**
          * Expose the FTFont <code>charSize</code> to our derived classes.
          *
          * @param The font to perform the query on.
          *
          * @return A reference to the charSize object of font.
          */
         FTSize &GetCharSize(FTFont *font)
            { return(font->charSize); }
};

#endif  /* __FTLayout__ */

