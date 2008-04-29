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

#ifndef __FTGLExtrdFont__
#define __FTGLExtrdFont__

#include <ftgl.h>

#ifdef __cplusplus


/**
 * FTGLExtrdFont is a specialisation of the FTFont class for handling
 * extruded Polygon fonts
 *
 * @see FTFont
 * @see FTGLPolygonFont
 */
class FTGL_EXPORT FTGLExtrdFont : public FTFont
{
    public:
        /**
         * Open and read a font file. Sets Error flag.
         *
         * @param fontFilePath  font file path.
         */
        FTGLExtrdFont(const char* fontFilePath);

        /**
         * Open and read a font from a buffer in memory. Sets Error flag.
         * The buffer is owned by the client and is NOT copied by FTGL. The
         * pointer must be valid while using FTGL.
         *
         * @param pBufferBytes  the in-memory buffer
         * @param bufferSizeInBytes  the length of the buffer in bytes
         */
        FTGLExtrdFont(const unsigned char *pBufferBytes,
                      size_t bufferSizeInBytes);

        /**
         * Destructor
         */
        ~FTGLExtrdFont();
};

#endif //__cplusplus

FTGL_BEGIN_C_DECLS
    FTGL_EXPORT FTGLfont *ftglCreateExtrdFont(const char *fontname);
FTGL_END_C_DECLS

#endif // __FTGLExtrdFont__

