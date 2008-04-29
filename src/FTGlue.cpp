/*
 * FTGL - OpenGL font library
 *
 * Copyright (c) 2001-2004 Henry Maddocks <ftgl@opengl.geek.nz>
 *               2008 Éric Beets <ericbeets@free.fr>
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

#include "config.h"

#include "FTInternals.h"

namespace C
{

//
//  C wrappers for FTFont
//

#define C_FUN(cret, cname, cargs, cxxerr, cxxname, cxxarg) \
    cret cname cargs \
    { \
        if(!f || !f->ptr) \
        { \
            fprintf(stderr, "FTGL warning: NULL pointer in %s\n", #cname); \
            cxxerr; \
        } \
        switch(f->type) \
        { \
            case FTGL::FONT_BITMAP: \
                return dynamic_cast<FTGLBitmapFont*>(f->ptr)->cxxname cxxarg; \
            case FTGL::FONT_EXTRUDE: \
                return dynamic_cast<FTGLExtrdFont*>(f->ptr)->cxxname cxxarg; \
            case FTGL::FONT_OUTLINE: \
                return dynamic_cast<FTGLOutlineFont*>(f->ptr)->cxxname cxxarg; \
            case FTGL::FONT_PIXMAP: \
                return dynamic_cast<FTGLPixmapFont*>(f->ptr)->cxxname cxxarg; \
            case FTGL::FONT_POLYGON: \
                return dynamic_cast<FTGLPolygonFont*>(f->ptr)->cxxname cxxarg; \
            case FTGL::FONT_TEXTURE: \
                return dynamic_cast<FTGLTextureFont*>(f->ptr)->cxxname cxxarg; \
        } \
        fprintf(stderr, "FTGL warning: %s not implemented for %d\n", #cname, f->type); \
        cxxerr; \
    }

// FTFont::~FTFont();
void ftglDestroyFont(FTGLfont *f)
{
    if(!f || !f->ptr)
    {
        fprintf(stderr, "FTGL warning: NULL pointer in %s\n", __FUNCTION__);
        return;
    }
    switch(f->type)
    {
        case FTGL::FONT_BITMAP:
            delete dynamic_cast<FTGLBitmapFont*>(f->ptr); break;
        case FTGL::FONT_EXTRUDE:
            delete dynamic_cast<FTGLExtrdFont*>(f->ptr); break;
        case FTGL::FONT_OUTLINE:
            delete dynamic_cast<FTGLOutlineFont*>(f->ptr); break;
        case FTGL::FONT_PIXMAP:
            delete dynamic_cast<FTGLPixmapFont*>(f->ptr); break;
        case FTGL::FONT_POLYGON:
            delete dynamic_cast<FTGLPolygonFont*>(f->ptr); break;
        case FTGL::FONT_TEXTURE:
            delete dynamic_cast<FTGLTextureFont*>(f->ptr); break;
        default:
            fprintf(stderr, "FTGL warning: %s not implemented for %d\n",
                            __FUNCTION__, f->type);
            break;
    }

    f->ptr = NULL;
}

// bool FTFont::Attach(const char* fontFilePath);
C_FUN(int, ftglAttachFile, (FTGLfont *f, const char* path),
      return 0, Attach, (path));

// bool FTFont::Attach(const unsigned char *pBufferBytes,
//                     size_t bufferSizeInBytes);
C_FUN(int, ftglAttachData, (FTGLfont *f, const unsigned char *p, size_t s),
      return 0, Attach, (p, s));

// bool FTFont::CharMap(FT_Encoding encoding);
C_FUN(int, ftglCharMap, (FTGLfont *f, FT_Encoding enc),
      return 0, CharMap, (enc));

// unsigned int FTFont::CharMapCount();
C_FUN(unsigned int, ftglCharMapCount, (FTGLfont *f),
      return 0, CharMapCount, ());

// FT_Encoding* FTFont::CharMapList();
C_FUN(FT_Encoding *, ftglCharMapList, (FTGLfont* f),
      return NULL, CharMapList, ());

// virtual bool FTFont::FaceSize(const unsigned int size,
//                               const unsigned int res = 72);
C_FUN(int, ftglSetFaceSize, (FTGLfont *f, unsigned int s),
      return 0, FaceSize, (s));
C_FUN(int, ftglSetFaceSizeRes, (FTGLfont *f, unsigned int s, unsigned int r),
      return 0, FaceSize, (s, r));

// unsigned int FTFont::FaceSize() const;
// XXX: need to call FaceSize() as FTFont::FaceSize() because of FTGLTexture
C_FUN(unsigned int, ftglGetFaceSize, (FTGLfont *f),
      return 0, FTFont::FaceSize, ());

// virtual void FTFont::Depth(float depth);
C_FUN(void, ftglSetDepth, (FTGLfont *f, float d), return, Depth, (d));

// virtual void FTFont::Outset(float front, float back);
C_FUN(void, ftglSetOutset, (FTGLfont *f, float front, float back),
      return, FTFont::Outset, (front, back));

// void FTFont::UseDisplayList(bool useList);
C_FUN(void, ftglUseDisplayList, (FTGLfont *f, int l),
      return, UseDisplayList, (l));

// float FTFont::Ascender() const;
C_FUN(float, ftglAscender, (FTGLfont *f), return 0.f, Ascender, ());

// float FTFont::Descender() const;
C_FUN(float, ftglDescender, (FTGLfont *f), return 0.f, Descender, ());

// float FTFont::LineHeight() const;
C_FUN(float, ftglLineHeight, (FTGLfont *f), return 0.f, LineHeight, ());

// void FTFont::BBox(const char* string, float& llx, float& lly, float& llz,
//                   float& urx, float& ury, float& urz);
C_FUN(void, ftglBBox, (FTGLfont *f, const char* s, float c[6]),
      return, BBox, (s, c[0], c[1], c[2], c[3], c[4], c[5]));

// float FTFont::Advance(const char* string);
C_FUN(float, ftglAdvance, (FTGLfont *f, const char* s),
      return 0.f, Advance, (s));

// virtual void FTFont::Render(const char* string);
C_FUN(void, ftglRender, (FTGLfont *f, const char * s), return, Render, (s));

// virtual void Render(const char* string, int renderMode);
C_FUN(void, ftglRenderMode, (FTGLfont *f, const char *s, int r),
      return, Render, (s, r));

// FT_Error FTFont::Error() const;
C_FUN(FT_Error, ftglError, (FTGLfont *f), return -1, Error, ());

#undef C_FUN

//
//  C wrappers for FTLayout
//

#define C_FUN(cret, cname, cargs, cxxerr, cxxname, cxxarg) \
    cret cname cargs \
    { \
        if(!f || !f->ptr) \
        { \
            fprintf(stderr, "FTGL warning: NULL pointer in %s\n", #cname); \
            cxxerr; \
        } \
        switch(f->type) \
        { \
            case FTGL::LAYOUT_SIMPLE: \
                return dynamic_cast<FTSimpleLayout*>(f->ptr)->cxxname cxxarg; \
        } \
        fprintf(stderr, "FTGL warning: %s not implemented for %d\n", #cname, f->type); \
        cxxerr; \
    }

// FTLayout::~FTLayout();
void ftglDestroyLayout(FTGLlayout *f)
{
    if(!f || !f->ptr)
    {
        fprintf(stderr, "FTGL warning: NULL pointer in %s\n", __FUNCTION__);
        return;
    }
    switch(f->type)
    {
        case FTGL::LAYOUT_SIMPLE:
            delete dynamic_cast<FTSimpleLayout*>(f->ptr); break;
        default:
            fprintf(stderr, "FTGL warning: %s not implemented for %d\n",
                            __FUNCTION__, f->type);
    }

    f->ptr = NULL;
}

// virtual void BBox(const char* string, float& llx, float& lly, float& llz, float& urx, float& ury, float& urz)
C_FUN(void, ftglLayoutBBox, (FTGLlayout *f, const char * s, float c[6]),
      return, BBox, (s, c[0], c[1], c[2], c[3], c[4], c[5]));

// virtual void Render(const char* string);
C_FUN(void, ftglLayoutRender, (FTGLlayout *f, const char *s),
      return, Render, (s));

// virtual void Render(const char* string, int renderMode);
C_FUN(void, ftglLayoutRenderMode, (FTGLlayout *f, const char *s, int r),
      return, Render, (s, r));

// void RenderSpace(const char *string, const float ExtraSpace = 0.0)
C_FUN(void, ftglLayoutRenderSpace, (FTGLlayout *f, const char *s,
        const float e), return, RenderSpace, (s, e));

// void SetFont(FTFont *fontInit)
void ftglLayoutSetFont(FTGLlayout *f, FTGLfont *font)
{
    if(!f || !f->ptr)
    {
        //XXX fprintf(stderr, "FTGL warning: NULL pointer in %s\n", __func__);
        return;
    }
    switch(f->type)
    {
        case FTGL::LAYOUT_SIMPLE:
            f->font = font;
            return dynamic_cast<FTSimpleLayout*>(f->ptr)->SetFont(font->ptr);
    }
    fprintf(stderr, "FTGL warning: %s not implemented for %d\n",
                    __FUNCTION__, f->type);
}

// FTFont *GetFont()
FTGLfont *ftglLayoutGetFont(FTGLlayout *f)
{
    if(!f || !f->ptr)
    {
        fprintf(stderr, "FTGL warning: NULL pointer in %s\n", __FUNCTION__);
        return NULL;
    }
    return f->font;
}

// void SetLineLength(const float LineLength);
C_FUN(void, ftglLayoutSetLineLength, (FTGLlayout *f, const float length),
      return, SetLineLength, (length));

// float GetLineLength() const
C_FUN(float, ftglLayoutGetLineLength, (FTGLlayout *f),
      return 0.0f, GetLineLength, ());

// void SetAlignment(const TextAlignment Alignment)
C_FUN(void, ftglLayoutSetAlignment, (FTGLlayout *f, FTGL::TextAlignment a),
      return, SetAlignment, (a));

// TextAlignment GetAlignment() const
C_FUN(FTGL::TextAlignment, ftglLayoutGetAlignement, (FTGLlayout *f),
      return FTGL::ALIGN_LEFT, GetAlignment, ());

// void SetLineSpacing(const float LineSpacing)
C_FUN(void, ftglLayoutSetLineSpacing, (FTGLlayout *f, const float l),
      return, SetLineSpacing, (l));

// float GetLineSpacing() const
C_FUN(float, ftglLayoutGetLineSpacing, (FTGLlayout *f),
      return 0.0f, GetLineSpacing, ());

} // namespace C

