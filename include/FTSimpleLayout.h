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

#ifndef    __FTSimpleLayout__
#define    __FTSimpleLayout__

#ifdef __cplusplus

#include "FTLayout.h"
#include "FTBBox.h"

class FTFont;
class FTSimpleLayoutImpl;


class FTGL_EXPORT FTSimpleLayout : public FTLayout
{
    public:
        /**
         * Initializes line spacing to 1.0, alignment to
         * ALIGN_LEFT and wrap to 100.0
         */
        FTSimpleLayout();

        /**
         * Destructor
         */
        ~FTSimpleLayout() {}

        /**
         * Set he font to use for rendering the text.
         *
         * @param fontInit A pointer to the new font.  The font is
         *                 referenced by this but will not be
         *                 disposed of when this is deleted.
         */
        void SetFont(FTFont *fontInit);

        /**
         * @return The current font.
         */
        FTFont *GetFont();

        /**
         * The maximum line length for formatting text.
         *
         * @param LineLength The new line length.
         */
        void SetLineLength(const float LineLength);

        /**
         * @return The current line length.
         */
        float GetLineLength() const;

        /**
         * The text alignment mode used to distribute
         * space within a line or rendered text.
         *
         * @param Alignment The new alignment mode.
         */
        void SetAlignment(const FTGL::TextAlignment Alignment);

        /**
         * @return The text alignment mode.
         */
        FTGL::TextAlignment GetAlignment() const;

        /**
         * Sets the line height.
         *
         * @param LineSpacing The height of each line of text expressed as
         *                    a percentage of the current fonts line height.
         */
        void SetLineSpacing(const float LineSpacing);

        /**
         * @return The line spacing.
         */
        float GetLineSpacing() const;

        /**
         * Render a string of characters and distribute extra space amongst
         * the whitespace regions of the string.
         *
         * @param string      'C' style string to output.
         * @param ExtraSpace  The amount of extra space to add to each run of
         *                    whitespace.
         */
        void RenderSpace(const char *string, const float ExtraSpace = 0.0);

        /**
         * Render a string of characters and distribute extra space amongst
         * the whitespace regions of the string.
         *
         * @param string      wchar_t string to output.
         * @param ExtraSpace  The amount of extra space to add to each run of
         *                    whitespace.
         */
        void RenderSpace(const wchar_t *string, const float ExtraSpace = 0.0);
};


class FTSimpleLayoutImpl : public FTLayoutImpl
{
    friend class FTSimpleLayout;

    public:
        FTSimpleLayoutImpl();

        ~FTSimpleLayoutImpl();

        /**
         * Get the bounding box for a string.
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
                          float& llz, float& urx, float& ury, float& urz);

        /**
         * Get the bounding box for a string.
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
                          float& llz, float& urx, float& ury, float& urz);

        /**
         * Render a string of characters
         *
         * @param string    'C' style string to be output.
         */
        virtual void Render(const char* string);

        /**
         * Render a string of characters
         *
         * @param string    'C' style string to be output.
         * @param renderMode    Render mode to display
         */
        virtual void Render(const char* string, int renderMode);

        /**
         * Render a string of characters
         *
         * @param string    wchar_t string to be output.
         */
        virtual void Render(const wchar_t* string);

        /**
         * Render a string of characters
         *
         * @param string    wchar_t string to be output.
         * @param renderMode    Render mode to display
         */
        virtual void Render(const wchar_t* string, int renderMode);

        /**
         * Render a string of characters and distribute extra space amongst
         * the whitespace regions of the string.
         *
         * @param string      'C' style string to output.
         * @param ExtraSpace  The amount of extra space to add to each run of
         *                    whitespace.
         */
        void RenderSpace(const char *string, const float ExtraSpace = 0.0);

        /**
         * Render a string of characters and distribute extra space amongst
         * the whitespace regions of the string.
         *
         * @param string      wchar_t string to output.
         * @param ExtraSpace  The amount of extra space to add to each run of
         *                    whitespace.
         */
        void RenderSpace(const wchar_t *string, const float ExtraSpace = 0.0);

   protected:
        /**
         * Render a string of characters and distribute extra space amongst
         * the whitespace regions of the string.  Note that this method
         * does not reset the pen position before rendering.  This method
         * provides the implementation for other RenderSpace methods and
         * thus should be overloaded when attempting to overload any
         * RenderSpace methods.
         *
         * @param string   A buffer of wchar_t characters to output.
         * @param start    The index of the first character in string to output.
         * @param end      The index of the last character in string to output.
         * @param renderMode Render mode to display
         * @param ExtraSpace The amount of extra space to distribute amongst
         *                   the characters.
         */
        virtual void RenderSpace(const char *string, const int start,
                                 const int end, int renderMode, const float ExtraSpace = 0.0);

        /**
         * Render a string of characters and distribute extra space amongst
         * the whitespace regions of the string.  Note that this method
         * does not reset the pen position before rendering.  This method
         * provides the implementation for other RenderSpace methods and
         * thus should be overloaded when attempting to overload any
         * RenderSpace methods.
         *
         * @param string   A buffer of wchar_t characters to output.
         * @param start    The index of the first character in string to output.
         * @param end      The index of the last character in string to output.
         * @param renderMode Render mode to display
         * @param ExtraSpace The amount of extra space to distribute amongst
         *                   the characters.
         */
        virtual void RenderSpace(const wchar_t *string, const int start,
                                 const int end, int renderMode, const float ExtraSpace = 0.0);

    private:
        /**
         * Either render a string of characters and wrap lines
         * longer than a threshold or compute the bounds
         * of a string of characters when wrapped.  The functionality
         * of this method is exposed by the BBoxWrapped and
         * RenderWrapped methods.
         *
         * @param buf         wchar_t style string to output.
         * @param renderMode  Render mode to display
         * @param bounds      A pointer to a bounds object.  If non null
         *                    the bounds of the text when laid out
         *                    will be stored in bounds.  If null the
         *                    text will be rendered.
         */
        virtual void WrapText(const char *buf, int renderMode, FTBBox *bounds = NULL);

        /**
         * Either render a string of characters and wrap lines
         * longer than a threshold or compute the bounds
         * of a string of characters when wrapped.  The functionality
         * of this method is exposed by the BBoxWrapped and
         * RenderWrapped methods.
         *
         * @param buf         wchar_t style string to output.
         * @param renderMode  Render mode to display
         * @param bounds      A pointer to a bounds object.  If non null
         *                    the bounds of the text when laid out
         *                    will be stored in bounds.  If null the
         *                    text will be rendered.
         */
        virtual void WrapText(const wchar_t *buf, int renderMode, FTBBox *bounds = NULL);

        /**
         * A helper method used by WrapText to either output the text or
         * compute it's bounds.
         *
         * @param buf      A pointer to an array of character data.
         * @param start    The index of the first character to process.
         * @param end      The index of the last character to process.  If
         *                 < 0 then characters will be parsed until a '\0'
         *                 is encountered.
         * @param RemainingWidth The amount of extra space left on the line.
         * @param bounds     A pointer to a bounds object.  If non null the
         *                   bounds will be initialized or expanded by the
         *                   bounds of the line.  If null the text will be
         *                   rendered.  If the bounds are invalid (lower > upper)
         *                   they will be initialized.  Otherwise they
         *                   will be expanded.
         * @param renderMode  Render mode to display
         */
        void OutputWrapped(const char *buf, const int start, const int end,
                           const float RemainingWidth, FTBBox *bounds, int renderMode);

        /**
         * A helper method used by WrapText to either output the text or
         * compute it's bounds.
         *
         * @param buf      A pointer to an array of character data.
         * @param start    The index of the first character to process.
         * @param end      The index of the last character to process.  If
         *                 < 0 then characters will be parsed until a '\0'
         *                 is encountered.
         * @param RemainingWidth The amount of extra space left on the line.
         * @param bounds     A pointer to a bounds object.  If non null the
         *                   bounds will be initialized or expanded by the
         *                   bounds of the line.  If null the text will be
         *                   rendered.  If the bounds are invalid (lower > upper)
         *                   they will be initialized.  Otherwise they
         *                   will be expanded.
         * @param renderMode  Render mode to display
         */
        void OutputWrapped(const wchar_t *buf, const int start, const int end,
                           const float RemainingWidth, FTBBox *bounds, int renderMode);

        /**
         * The font to use for rendering the text.  The font is
         * referenced by this but will not be disposed of when this
         * is deleted.
         */
        FTFont *currentFont;

        /**
         * The maximum line length for formatting text.
         */
        float lineLength;

        /**
         * The text alignment mode used to distribute
         * space within a line or rendered text.
         */
        FTGL::TextAlignment alignment;

        /**
         * The height of each line of text expressed as
         * a percentage of the font's line height.
         */
        float lineSpacing;

        /* Internal generic BBox() implementation */
        template <typename T>
        inline void BBoxI(const T* string, float& llx, float& lly, float& llz,
                          float& urx, float& ury, float& urz);

        /* Internal generic Render() implementation */
        template <typename T>
        inline void RenderI(const T* string, int renderMode);

        /* Internal generic RenderSpace() implementation */
        template <typename T>
        inline void RenderSpaceI(const T* string, const int start,
                                 const int end, int renderMode, const float ExtraSpace = 0.0);

        /* Internal generic WrapText() implementation */
        template <typename T>
        void WrapTextI(const T* buf, int renderMode, FTBBox *bounds = NULL);

        /* Internal generic OutputWrapped() implementation */
        template <typename T>
        void OutputWrappedI(const T* buf, const int start, const int end,
                            const float RemainingWidth, FTBBox *bounds, int renderMode);
};


#endif //__cplusplus

#ifdef __cplusplus
extern "C" {
namespace C {
#endif

FTGL_EXPORT void  ftglLayoutBBox           (FTGLlayout *, const char*, float []);

FTGL_EXPORT void  ftglLayoutRender         (FTGLlayout *, const char*);
FTGL_EXPORT void  ftglLayoutRenderMode     (FTGLlayout *, const char*, int);
FTGL_EXPORT void  ftglLayoutRenderSpace    (FTGLlayout *, const float);

FTGL_EXPORT void      ftglLayoutSetFont    (FTGLlayout *, FTGLfont*);
FTGL_EXPORT FTGLfont* ftglLayoutGetFont    (FTGLlayout *);

FTGL_EXPORT void  ftglLayoutSetLineLength  (FTGLlayout *, const float);
FTGL_EXPORT float ftglLayoutGetLineLength  (FTGLlayout *);

#ifdef __cplusplus
FTGL_EXPORT void                ftglLayoutSetAlignment   (FTGLlayout *, const FTGL::TextAlignment);
FTGL_EXPORT FTGL::TextAlignment ftglLayoutGetAlignement  (FTGLlayout *);
#else
FTGL_EXPORT void                ftglLayoutSetAlignment   (FTGLlayout *, const TextAlignment);
FTGL_EXPORT int                 ftglLayoutGetAlignement  (FTGLlayout *);
#endif

FTGL_EXPORT void  ftglLayoutSetLineSpacing (FTGLlayout *, const float);
FTGL_EXPORT float ftglLayoutGetLineSpacing (FTGLlayout *);

#ifdef __cplusplus
}
}
#endif

#endif  /* __FTSimpleLayout__ */

