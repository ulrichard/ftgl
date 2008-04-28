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

#include "config.h"

#include "FTFace.h"
#include "FTFont.h"
#include "FTGlyphContainer.h"
#include "FTBBox.h"

FTFont::FTFont(const char* fontFilePath)
:   face(fontFilePath),
    useDisplayLists(true),
    glyphList(0)
{
    err = face.Error();
    if(err == 0)
    {
        glyphList = new FTGlyphContainer(&face);
    }
}


FTFont::FTFont(const unsigned char *pBufferBytes, size_t bufferSizeInBytes)
:   face(pBufferBytes, bufferSizeInBytes),
    glyphList(0)
{
    err = face.Error();
    if(err == 0)
    {
        glyphList = new FTGlyphContainer(&face);
    }
}


FTFont::~FTFont()
{
    if(glyphList)
    {
        delete glyphList;
    }
}


bool FTFont::Attach(const char* fontFilePath)
{
    if(face.Attach(fontFilePath))
    {
        err = 0;
        return true;
    }
    else
    {
        err = face.Error();
        return false;
    }
}


bool FTFont::Attach(const unsigned char *pBufferBytes, size_t bufferSizeInBytes)
{
    if(face.Attach(pBufferBytes, bufferSizeInBytes))
    {
        err = 0;
        return true;
    }
    else
    {
        err = face.Error();
        return false;
    }
}


bool FTFont::FaceSize(const unsigned int size, const unsigned int res)
{
    charSize = face.Size(size, res);
    err = face.Error();

    if(err != 0)
    {
        return false;
    }

    if(glyphList != NULL)
    {
        delete glyphList;
    }

    glyphList = new FTGlyphContainer(&face);
    return true;
}


unsigned int FTFont::FaceSize() const
{
    return charSize.CharSize();
}


bool FTFont::CharMap(FT_Encoding encoding)
{
    bool result = glyphList->CharMap(encoding);
    err = glyphList->Error();
    return result;
}


unsigned int FTFont::CharMapCount()
{
    return face.CharMapCount();
}


FT_Encoding* FTFont::CharMapList()
{
    return face.CharMapList();
}


void FTFont::UseDisplayList(bool useList)
{
    useDisplayLists = useList;
}

float FTFont::Ascender() const
{
    return charSize.Ascender();
}


float FTFont::Descender() const
{
    return charSize.Descender();
}


float FTFont::LineHeight() const
{
    return charSize.Height();
}


template <typename T>
inline void FTFont::BBoxI(const T* string, const int start, const int end,
                          float& llx, float& lly, float& llz,
                          float& urx, float& ury, float& urz)
{
    FTBBox totalBBox;

    /* Only compute the bounds if string is non-empty. */
    if(string && ('\0' != string[start]))
    {
        float advance = 0;

        if(CheckGlyph(string[start]))
        {
            totalBBox = glyphList->BBox(string[start]);
            advance = glyphList->Advance(string[start], string[start + 1]);
        }

        /* Expand totalBox by each glyph in String (for idx) */
        for(int i = start + 1; (end < 0 && string[i])
                                 || (end >= 0 && i < end); i++)
        {
            if(CheckGlyph(string[i]))
            {
                FTBBox tempBBox = glyphList->BBox(string[i]);
                tempBBox.Move(FTPoint(advance, 0.0f, 0.0f));

                totalBBox += tempBBox;
                advance += glyphList->Advance(string[i], string[i + 1]);
            }
        }
    }

    // TODO: The Z values do not follow the proper ordering.  I'm not sure why.
    llx = totalBBox.lowerX < totalBBox.upperX ? totalBBox.lowerX : totalBBox.upperX;
    lly = totalBBox.lowerY < totalBBox.upperY ? totalBBox.lowerY : totalBBox.upperY;
    llz = totalBBox.lowerZ < totalBBox.upperZ ? totalBBox.lowerZ : totalBBox.upperZ;
    urx = totalBBox.lowerX > totalBBox.upperX ? totalBBox.lowerX : totalBBox.upperX;
    ury = totalBBox.lowerY > totalBBox.upperY ? totalBBox.lowerY : totalBBox.upperY;
    urz = totalBBox.lowerZ > totalBBox.upperZ ? totalBBox.lowerZ : totalBBox.upperZ;
}


void FTFont::BBox(const char* string, const int start, const int end,
                  float& llx, float& lly, float& llz,
                  float& urx, float& ury, float& urz)
{
    return BBoxI(string, start, end, llx, lly, llz, urx, ury, urz);
}


void FTFont::BBox(const wchar_t* string, const int start, const int end,
                  float& llx, float& lly, float& llz,
                  float& urx, float& ury, float& urz)
{
    return BBoxI(string, start, end, llx, lly, llz, urx, ury, urz);
}


template <typename T>
inline float FTFont::AdvanceI(const T* string)
{
    const T* c = string;
    float width = 0.0f;

    while(*c)
    {
        if(CheckGlyph(*c))
        {
            width += glyphList->Advance(*c, *(c + 1));
        }
        ++c;
    }

    return width;
}


float FTFont::Advance(const wchar_t* string)
{
    return AdvanceI(string);
}


float FTFont::Advance(const char* string)
{
    return AdvanceI((const unsigned char *)string);
}


/* FIXME: DoRender should disappear, see commit [853]. */
void FTFont::DoRender(const unsigned int chr,
                      const unsigned int nextChr, FTPoint &origin, int renderMode)
{
    if(CheckGlyph(chr))
    {
        FTPoint kernAdvance = glyphList->Render(chr, nextChr, origin, renderMode);
        origin += kernAdvance;
    }
}


template <typename T>
inline void FTFont::RenderI(const T* string, int renderMode)
{
    const T* c = string;
    pen = FTPoint(0., 0.);

    while(*c)
    {
        DoRender(*c, *(c + 1), pen, renderMode);
        ++c;
    }
}


void FTFont::Render(const wchar_t* string)
{
    RenderI(string, FTGL::RENDER_FRONT | FTGL::RENDER_BACK | FTGL::RENDER_SIDE);
}


void FTFont::Render(const char * string)
{
    RenderI((const unsigned char *)string, FTGL::RENDER_FRONT |
                                           FTGL::RENDER_BACK |
                                           FTGL::RENDER_SIDE);
}


void FTFont::Render(const char * string, int renderMode)
{
    RenderI((const unsigned char *)string, renderMode);
}


void FTFont::Render(const wchar_t* string, int renderMode)
{
    RenderI(string, renderMode);
}


bool FTFont::CheckGlyph(const unsigned int characterCode)
{
    if(NULL == glyphList->Glyph(characterCode))
    {
        unsigned int glyphIndex = glyphList->FontIndex(characterCode);
        FTGlyph* tempGlyph = MakeGlyph(glyphIndex);
        if(NULL == tempGlyph)
        {
            if(0 == err)
            {
                err = 0x13;
            }

            return false;
        }
        glyphList->Add(tempGlyph, characterCode);
    }

    return true;
}

