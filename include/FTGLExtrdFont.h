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

#ifndef __FTGLExtrdFont__
#define __FTGLExtrdFont__

#ifdef __cplusplus

#include "FTFont.h"
#include "FTGL.h"


class FTGlyph;

/**
 * FTGLExtrdFont is a specialisation of the FTFont class for handling
 * extruded Polygon fonts
 *
 * @see		FTFont
 * @see		FTGLPolygonFont
 */
class FTGL_EXPORT FTGLExtrdFont : public FTFont
{
    public:
        /**
         * Open and read a font file. Sets Error flag.
         *
         * @param fontFilePath  font file path.
         */
        FTGLExtrdFont( const char* fontFilePath);

        /**
         * Open and read a font from a buffer in memory. Sets Error flag.
         *
         * @param pBufferBytes  the in-memory buffer
         * @param bufferSizeInBytes  the length of the buffer in bytes
         */
        FTGLExtrdFont( const unsigned char *pBufferBytes, size_t bufferSizeInBytes);

        /**
         * Destructor
         */
        ~FTGLExtrdFont();
		
        /**
         * Set the extrusion distance for the font. 
         *
         * @param d  The extrusion distance.
         */
        void Depth( float d) { depth = d;}
		
    private:
        /**
         * Construct a FTPolyGlyph.
         *
         * @param glyphIndex The glyph index NOT the char code.
         * @return	An FTExtrdGlyph or <code>null</code> on failure.
         */
        inline virtual FTGlyph* MakeGlyph( unsigned int glyphIndex);
		
        /**
         * The extrusion distance for the font. 
         */
        float depth;
};

#endif //__cplusplus

#ifdef __cplusplus
extern "C" {
namespace C {
#endif
FTGL_EXPORT FTGLfont *ftglExtrdFontMake(const char *fontname);
#ifdef __cplusplus
}
}
#endif

#endif	//	__FTGLExtrdFont__

