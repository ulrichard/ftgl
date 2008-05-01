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

#ifndef __ftgl__
#   warning This header is deprecated. Please use <FTGL/ftgl.h> from now.
#   include <FTGL/ftgl.h>
#endif

#ifndef __FTGlyph__
#define __FTGlyph__

#ifdef __cplusplus

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

    public:
        virtual ~FTGlyph();

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

#endif //__cplusplus

FTGL_BEGIN_C_DECLS

FTGL_EXPORT FTGLglyph *ftglCreateBitmapGlyph(FT_GlyphSlot glyph);
FTGL_EXPORT FTGLglyph *ftglCreateExtrudeGlyph(FT_GlyphSlot glyph, float depth,
                                float frontOutset, float backOutset,
                                int useDisplayList);
FTGL_EXPORT FTGLglyph *ftglCreateOutlineGlyph(FT_GlyphSlot glyph, float outset,
                                  int useDisplayList);
FTGL_EXPORT FTGLglyph *ftglCreatePixmapGlyph(FT_GlyphSlot glyph);
FTGL_EXPORT FTGLglyph *ftglCreatePolyGlyph(FT_GlyphSlot glyph, float outset,
                               int useDisplayList);
FTGL_EXPORT FTGLglyph *ftglCreateTextureGlyph(FT_GlyphSlot glyph, int id,
                                              int xOffset, int yOffset,
                                              int width, int height);

FTGL_EXPORT void ftglDestroyGlyph(FTGLglyph *g);

FTGL_EXPORT void ftglGlyphRender(FTGLglyph *g, FTGL_DOUBLE penx,
                                 FTGL_DOUBLE peny, int renderMode,
                                 FTGL_DOUBLE *advancex, FTGL_DOUBLE *advancey);
FTGL_EXPORT void ftglGlyphAdvance(FTGLglyph *g, FTGL_DOUBLE *advancex,
                                  FTGL_DOUBLE *advancey);
FTGL_EXPORT void ftglGlyphBBox(FTGLglyph *g, float *lx, float *ly, float *lz,
                               float *ux, float *uy, float *uz);

FTGL_END_C_DECLS

#endif  //  __FTGlyph__

