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

#ifndef    __FTFont__
#define    __FTFont__

#include <ft2build.h>

#include FT_FREETYPE_H

#ifdef __cplusplus

#include "FTFace.h"
#include "FTGL.h"

class FTGlyphContainer;
class FTGlyph;
class FTLayout;


/**
 * FTFont is the public interface for the FTGL library.
 *
 * Specific font classes are derived from this class. It uses the helper
 * classes FTFace and FTSize to access the Freetype library. This class
 * is abstract and deriving classes must implement the protected
 * <code>MakeGlyph</code> function to create glyphs of the
 * appropriate type.
 *
 * It is good practice after using these functions to test the error
 * code returned. <code>FT_Error Error()</code>. Check the freetype file fterrdef.h
 * for error definitions.
 *
 * @see     FTFace
 * @see     FTSize
 * @see     FTGlyphContainer
 * @see     FTGlyph
 */
class FTGL_EXPORT FTFont
{
    public:
        /**
         * Open and read a font file. Sets Error flag.
         *
         * @param fontFilePath  font file path.
         */
        FTFont(const char* fontFilePath);

        /**
         * Open and read a font from a buffer in memory. Sets Error flag.
         * The buffer is owned by the client and is NOT copied by FTGL. The
         * pointer must be valid while using FTGL.
         *
         * @param pBufferBytes  the in-memory buffer
         * @param bufferSizeInBytes  the length of the buffer in bytes
         */
        FTFont(const unsigned char *pBufferBytes, size_t bufferSizeInBytes);

        /**
         * Destructor
         */
        virtual ~FTFont();

        /**
         * Attach auxilliary file to font e.g font metrics.
         *
         * Note: not all font formats implement this function.
         *
         * @param fontFilePath  auxilliary font file path.
         * @return          <code>true</code> if file has been attached
         *                  successfully.
         */
        bool Attach(const char* fontFilePath);

        /**
         * Attach auxilliary data to font e.g font metrics, from memory
         *
         * Note: not all font formats implement this function.
         *
         * @param pBufferBytes  the in-memory buffer
         * @param bufferSizeInBytes  the length of the buffer in bytes
         * @return          <code>true</code> if file has been attached
         *                  successfully.
         */
        bool Attach(const unsigned char *pBufferBytes,
                    size_t bufferSizeInBytes);

        /**
         * Set the character map for the face.
         *
         * @param encoding      Freetype enumerate for char map code.
         * @return              <code>true</code> if charmap was valid and
         *                      set correctly
         */
        bool CharMap(FT_Encoding encoding);

        /**
         * Get the number of character maps in this face.
         *
         * @return character map count.
         */
        unsigned int CharMapCount();

        /**
         * Get a list of character maps in this face.
         *
         * @return pointer to the first encoding.
         */
        FT_Encoding* CharMapList();

        /**
         * Set the char size for the current face.
         *
         * @param size      the face size in points (1/72 inch)
         * @param res       the resolution of the target device.
         * @return          <code>true</code> if size was set correctly
         */
        virtual bool FaceSize(const unsigned int size,
                              const unsigned int res = 72);

        /**
         * Get the current face size in points.
         *
         * @return face size
         */
        unsigned int FaceSize() const;

        /**
         * Set the extrusion distance for the font. Only implemented by
         * FTGLExtrdFont
         *
         * @param depth  The extrusion distance.
         */
        virtual void Depth(float depth);

        /**
         * Set the outset distance for the font. Only implemented by
         * FTGLOutlineFont, FTGLPolygonFont and FTGLExtrdFont
         *
         * @param outset  The outset distance.
         */
        virtual void Outset(float outset);

        /**
         * Set the front and back outset distances for the font. Only
         * implemented by FTGLExtrdFont
         *
         * @param front  The front outset distance.
         * @param back   The back outset distance.
         */
        virtual void Outset(float front, float back);

        /**
         * Enable or disable the use of Display Lists inside FTGL
         *
         * @param  useList <code>true</code> turns ON display lists.
         *                 <code>false</code> turns OFF display lists.
         */
        void UseDisplayList(bool useList);

        /**
         * Get the global ascender height for the face.
         *
         * @return  Ascender height
         */
        float Ascender() const;

        /**
         * Gets the global descender height for the face.
         *
         * @return  Descender height
         */
        float Descender() const;

        /**
         * Gets the line spacing for the font.
         *
         * @return  Line height
         */
        float LineHeight() const;

        /**
         * Get the bounding box for a string.
         *
         * @param string    a char buffer
         * @param start     The index of the first character of string
         *                  to check.
         * @param end       The index of the last character of string to
         *                  check.  If < 0 then characters will be parsed
         *                  until a '\0' is encountered.
         * @param llx       lower left near x coord
         * @param lly       lower left near y coord
         * @param llz       lower left near z coord
         * @param urx       upper right far x coord
         * @param ury       upper right far y coord
         * @param urz       upper right far z coord
         */
        void BBox(const char *string, const int start, const int end,
                  float& llx, float& lly, float& llz,
                  float& urx, float& ury, float& urz);

        /**
         * Get the bounding box for a string.
         *
         * @param string    a wchar_t buffer
         * @param start     The index of the first character of string
         *                  to check.
         * @param end       The index of the last character of string
         *                  to check.    If < 0 then characters will
         *                  be parsed until a '\0' is encountered.
         * @param llx       lower left near x coord
         * @param lly       lower left near y coord
         * @param llz       lower left near z coord
         * @param urx       upper right far x coord
         * @param ury       upper right far y coord
         * @param urz       upper right far z coord
         */
        void BBox(const wchar_t *string, const int start, const int end,
                  float& llx, float& lly, float& llz,
                  float& urx, float& ury, float& urz);

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
        void BBox(const char* string, float& llx, float& lly, float& llz,
                  float& urx, float& ury, float& urz);

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
        void BBox(const wchar_t* string, float& llx, float& lly, float& llz,
                  float& urx, float& ury, float& urz);

        /**
         * Get the advance width for a string.
         *
         * @param string    a wchar_t string
         * @return      advance width
         */
        float Advance(const wchar_t* string);

        /**
         * Get the advance width for a string.
         *
         * @param string    a char string
         * @return      advance width
         */
        float Advance(const char* string);

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
        virtual void Render(const wchar_t *string, int renderMode);

        /**
         * Queries the Font for errors.
         *
         * @return  The current error code.
         */
        FT_Error Error() const;

    protected:
        /**
         * Construct a glyph of the correct type.
         *
         * Clients must overide the function and return their specialised
         * FTGlyph.
         *
         * @param g The glyph index NOT the char code.
         * @return  An FT****Glyph or <code>null</code> on failure.
         */
        virtual FTGlyph* MakeGlyph(unsigned int g) = 0;

        /**
         * Current face object
         */
        FTFace face;

        /**
         * Current size object
         */
        FTSize charSize;

        /**
         * Flag to enable or disable the use of Display Lists inside FTGL
         * <code>true</code> turns ON display lists.
         * <code>false</code> turns OFF display lists.
         */
        bool useDisplayLists;

        /**
         * Current error code. Zero means no error.
         */
        FT_Error err;

    private:
        /**
         * Render a character.
         * This function does an implicit conversion on its arguments.
         *
         * @param chr       current character
         * @param nextChr   next character
         * @param origin       The position of the origin of the character.
         *                  After rendering the point referenced by origin
         *                  will be incremented by the kerning advance of
         *                  char and nextChr.
         * @param renderMode    Render mode to display
         */
        void DoRender(const unsigned int chr,
                      const unsigned int nextChr, FTPoint &origin,
                      int renderMode);

        /**
         * Check that the glyph at <code>chr</code> exist. If not load it.
         *
         * @param chr  character index
         * @return <code>true</code> if the glyph can be created.
         */
        bool CheckGlyph(const unsigned int chr);

        /**
         * An object that holds a list of glyphs
         */
        FTGlyphContainer* glyphList;

        /**
         * Current pen or cursor position;
         */
        FTPoint pen;

        /* Internal generic BBox() implementation */
        template <typename T>
        inline void BBoxI(const T *string, const int start, const int end,
                          float& llx, float& lly, float& llz,
                          float& urx, float& ury, float& urz);

        /* Internal generic BBox() implementation */
        template <typename T>
        inline float AdvanceI(const T* string);

        /* Internal generic Render() implementation */
        template <typename T>
        inline void RenderI(const T* string, int renderMode);

        /* Allow FTLayout classes to access DoRender and CheckGlyph */
        friend class FTLayout;
};

#endif //__cplusplus

#ifdef __cplusplus
extern "C" {
namespace C {
#endif

typedef struct FTGLfont FTGLfont;

FTGL_EXPORT void ftglDestroyFont(FTGLfont*);

FTGL_EXPORT int ftglAttachFile (FTGLfont*, const char*);
FTGL_EXPORT int ftglAttachData (FTGLfont*, const unsigned char *, size_t);

FTGL_EXPORT int          ftglCharMap      (FTGLfont*, FT_Encoding);
FTGL_EXPORT unsigned int ftglCharMapCount (FTGLfont*);
FTGL_EXPORT FT_Encoding* CharMapList      (FTGLfont*);

FTGL_EXPORT int          ftglSetFaceSize    (FTGLfont*, unsigned int);
FTGL_EXPORT int          ftglSetFaceSizeRes (FTGLfont*,
                                             unsigned int, unsigned int);
FTGL_EXPORT unsigned int ftglGetFaceSize    (FTGLfont*);
FTGL_EXPORT void         ftglSetDepth       (FTGLfont*, float);
FTGL_EXPORT void         ftglSetOutset      (FTGLfont*, float, float);

FTGL_EXPORT void ftglUseDisplayList (FTGLfont*, int);

FTGL_EXPORT float ftglAscender   (FTGLfont*);
FTGL_EXPORT float ftglDescender  (FTGLfont*);
FTGL_EXPORT float ftglLineHeight (FTGLfont*);
FTGL_EXPORT void  ftglBBox       (FTGLfont*, const char *, float[]);
FTGL_EXPORT float ftglAdvance    (FTGLfont*, const char *);
FTGL_EXPORT void  ftglRender     (FTGLfont*, const char *);
FTGL_EXPORT void  ftglRenderMode (FTGLfont*, const char *, int);

FTGL_EXPORT FT_Error ftglError (FTGLfont*);

#ifdef __cplusplus
}
}
#endif

#endif  //  __FTFont__


