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

#ifndef __FTGLBufferFontImpl__
#define __FTGLBufferFontImpl__

#include "FTGLBufferFont.h"
#include "FTFontImpl.h"

class FTGlyph;
class FTFontImpl;

class FTGLBufferFontImpl : public FTFontImpl
{
        friend class FTGLBufferFont;

    public:
        FTGLBufferFontImpl(const char* fontFilePath);

        FTGLBufferFontImpl(const unsigned char *pBufferBytes,
                           size_t bufferSizeInBytes);

        ~FTGLBufferFontImpl();

        /**
         * Renders a string of characters
         *
         * @param string    'C' style string to be output.
         */
        void Render(const char* string);

        /**
         * Renders a string of characters
         *
         * @param string    wchar_t string to be output.
         */
        void Render(const wchar_t* string);

    private:
        /**
         * Construct a FTBufferGlyph.
         *
         * @param g The glyph index NOT the char code.
         * @return  An FTBufferGlyph or <code>null</code> on failure.
         */
        inline virtual FTGlyph* MakeGlyph(unsigned int g);

        unsigned char* buffer;
};

#endif  //  __FTGLBufferFontImpl__

