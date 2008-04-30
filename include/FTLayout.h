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

#ifndef __FTLayout__
#define __FTLayout__

#include <ftgl.h>

#ifdef __cplusplus


class FTLayoutImpl;

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
    protected:
        FTLayout();

        virtual ~FTLayout();

    public:
        void BBox(const char* string, float& llx, float& lly,
                  float& llz, float& urx, float& ury, float& urz);

        void BBox(const wchar_t* string, float& llx, float& lly,
                  float& llz, float& urx, float& ury, float& urz);

        void Render(const char *string);

        void Render(const char *string, int renderMode);

        void Render(const wchar_t *string);

        void Render(const wchar_t *string, int renderMode);

        FT_Error Error() const;

    protected:
        FTLayoutImpl *impl;
};

#endif //__cplusplus

FTGL_BEGIN_C_DECLS

FTGL_EXPORT void ftglDestroyLayout(FTGLlayout*);

FTGL_EXPORT void  ftglLayoutBBox (FTGLlayout *, const char*, float []);

FTGL_EXPORT void  ftglLayoutRender      (FTGLlayout *, const char*);
FTGL_EXPORT void  ftglLayoutRenderMode  (FTGLlayout *, const char *, int);
FTGL_EXPORT void  ftglLayoutRenderSpace (FTGLlayout *, const char *, float);

FTGL_EXPORT void      ftglLayoutSetFont (FTGLlayout *, FTGLfont*);
FTGL_EXPORT FTGLfont* ftglLayoutGetFont (FTGLlayout *);

FTGL_EXPORT void  ftglLayoutSetLineLength  (FTGLlayout *, const float);
FTGL_EXPORT float ftglLayoutGetLineLength  (FTGLlayout *);

#ifdef __cplusplus /*FIXME: Éric, this is WRONG */
FTGL_EXPORT void                ftglLayoutSetAlignment   (FTGLlayout *, const FTGL::TextAlignment);
FTGL_EXPORT FTGL::TextAlignment ftglLayoutGetAlignement  (FTGLlayout *);
#else
FTGL_EXPORT void                ftglLayoutSetAlignment   (FTGLlayout *, const int);
FTGL_EXPORT int                 ftglLayoutGetAlignement  (FTGLlayout *);
#endif

FTGL_EXPORT void  ftglLayoutSetLineSpacing (FTGLlayout *, const float);
FTGL_EXPORT float ftglLayoutGetLineSpacing (FTGLlayout *);

FTGL_END_C_DECLS

#endif  /* __FTLayout__ */


