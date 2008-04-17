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

#include <ctype.h>

#include "FTFont.h"
#include "FTGlyphContainer.h"
#include "FTBBox.h"

#include "FTSimpleLayout.h"


FTSimpleLayout::FTSimpleLayout()
{
    currentFont = NULL;
    lineLength = 100.0f;
    alignment = ALIGN_LEFT;
    lineSpacing = 1.0f;
}


template <typename T>
inline void FTSimpleLayout::BBoxI(const T* string,
                                  float& llx, float& lly, float& llz,
                                  float& urx, float& ury, float& urz)
{
    FTBBox bounds;

    WrapText(string, &bounds);
    llx = bounds.lowerX; lly = bounds.lowerY; llz = bounds.lowerZ;
    urx = bounds.upperX; ury = bounds.upperY; urz = bounds.upperZ;
}


void FTSimpleLayout::BBox(const char *string, float& llx, float& lly,
                          float& llz, float& urx, float& ury, float& urz)
{
    BBoxI(string, llx, lly, llz, urx, ury, urz);
}


void FTSimpleLayout::BBox(const wchar_t *string, float& llx, float& lly,
                          float& llz, float& urx, float& ury, float& urz)
{
    BBoxI(string, llx, lly, llz, urx, ury, urz);
}


template <typename T>
inline void FTSimpleLayout::RenderI(const T *string)
{
    pen = FTPoint(0.0f, 0.0f);
    WrapText(string, NULL);
}


void FTSimpleLayout::Render(const char *string)
{
    RenderI(string);
}


void FTSimpleLayout::Render(const wchar_t* string)
{
    RenderI(string);
}


template <typename T>
inline void FTSimpleLayout::WrapTextI(const T *buf, FTBBox *bounds)
{
    int breakIdx = 0;          // index of the last break character
    int lineStart = 0;         // character index of the line start
    float nextStart = 0.0;     // total width of the current line
    float breakWidth = 0.0;    // width of the line up to the last word break
    float currentWidth = 0.0;  // width of all characters on the current line
    float prevWidth;           // width of all characters but the current glyph
    float wordLength = 0.0;    // length of the block since the last break char
    float glyphWidth, advance;
    FTBBox glyphBounds;

    // Reset the pen position
    pen.Y(0);

    // If we have bounds mark them invalid
    if(bounds)
    {
        bounds->Invalidate();
    }

    // Scan the input for all characters that need output
    for(int i = 0; buf[i]; i++)
    {
        // Find the width of the current glyph
        CheckGlyph(currentFont, buf[i]);
        glyphBounds = GetGlyphs(currentFont)->BBox(buf[i]);
        glyphWidth = glyphBounds.upperX - glyphBounds.lowerX;

        advance = GetGlyphs(currentFont)->Advance(buf[i], buf[i + 1]);
        prevWidth = currentWidth;
        // Compute the width of all glyphs up to the end of buf[i]
        currentWidth = nextStart + glyphWidth;
        // Compute the position of the next glyph
        nextStart += advance;

        // See if buf[i] is a space, a break or a regular character
        if((currentWidth > lineLength) || (buf[i] == '\n'))
        {
            // A non whitespace character has exceeded the line length.  Or a
            // newline character has forced a line break.  Output the last
            // line and start a new line after the break character.
            // If we have not yet found a break, break on the last character
            if(!breakIdx || (buf[i] == '\n'))
            {
                // Break on the previous character
                breakIdx = i - 1;
                breakWidth = prevWidth;
                // None of the previous words will be carried to the next line
                wordLength = 0;
                // If the current character is a newline discard its advance
                if(buf[i] == '\n') advance = 0;
            }

            float remainingWidth = lineLength - breakWidth;

            // Render the current substring
            // If the break character is a newline do not render it
            if(buf[breakIdx + 1] == '\n')
            {
                breakIdx++;
                OutputWrapped(buf, lineStart, breakIdx - 1,
                              remainingWidth, bounds);
            }
            else
            {
                OutputWrapped(buf, lineStart, breakIdx, remainingWidth, bounds);
            }

            // Store the start of the next line
            lineStart = breakIdx + 1;
            // TODO: Is Height() the right value here?
            pen -= FTPoint(0, GetCharSize(currentFont).Height() * lineSpacing);
            // The current width is the width since the last break
            nextStart = wordLength + advance;
            wordLength += advance;
            currentWidth = wordLength + advance;
            // Reset the safe break for the next line
            breakIdx = 0;
        }
        else if(isspace(buf[i]))
        {
            // This is the last word break position
            wordLength = 0;
            breakIdx = i;

            // Check to see if this is the first whitespace character in a run
            if(!i || !isspace(buf[i - 1]))
            {
                // Record the width of the start of the block
                breakWidth = currentWidth;
            }
        }
        else
        {
            wordLength += advance;
        }
    }

    float remainingWidth = lineLength - currentWidth;
    // Render any remaining text on the last line
    // Disable justification for the last row
    if(alignment == ALIGN_JUST)
    {
        alignment = ALIGN_LEFT;
        OutputWrapped(buf, lineStart, -1, remainingWidth, bounds);
        alignment = ALIGN_JUST;
    }
    else
    {
        OutputWrapped(buf, lineStart, -1, remainingWidth, bounds);
    }
}


void FTSimpleLayout::WrapText(const char *buf, FTBBox *bounds)
{
    WrapTextI(buf, bounds);
}


void FTSimpleLayout::WrapText(const wchar_t* buf, FTBBox *bounds)
{
    WrapTextI(buf, bounds);
}


template <typename T>
inline void FTSimpleLayout::OutputWrappedI(const T *buf, const int start,
                                           const int end,
                                           const float RemainingWidth,
                                           FTBBox *bounds)
{
    float distributeWidth = 0.0;
    // Align the text according as specified by Alignment
    switch (alignment)
    {
        case ALIGN_LEFT:
            pen.X(0);
            break;
        case ALIGN_CENTER:
            pen.X(RemainingWidth / 2);
            break;
        case ALIGN_RIGHT:
            pen.X(RemainingWidth);
            break;
        case ALIGN_JUST:
            pen.X(0);
            distributeWidth = RemainingWidth;
            break;
    }

    // If we have bounds expand them by the line's bounds, otherwise render
    // the line.
    if(bounds)
    {
        float llx, lly, llz, urx, ury, urz;
        currentFont->BBox(buf, start, end, llx, lly, llz, urx, ury, urz);

        // Add the extra space to the upper x dimension
        urx += distributeWidth;
        // TODO: It's a little silly to convert from a FTBBox to floats and
        // back again, but I don't want to implement yet another method for
        // finding the bounding box as a BBox.
        FTBBox temp(llx, lly, llz, urx, ury, urz);
        temp.Move(FTPoint(pen.X(), pen.Y(), 0.0f));

        // See if this is the first area to be added to the bounds
        if(!bounds->IsValid())
        {
            *bounds = temp;
        }
        else
        {
            *bounds += temp;
        }
    }
    else
    {
        RenderSpace(buf, start, end, distributeWidth);
    }
}


void FTSimpleLayout::OutputWrapped(const char *buf, const int start,
                                   const int end, const float RemainingWidth,
                                   FTBBox *bounds)
{
    OutputWrappedI(buf, start, end, RemainingWidth, bounds);
}


void FTSimpleLayout::OutputWrapped(const wchar_t *buf, const int start,
                                   const int end, const float RemainingWidth,
                                   FTBBox *bounds)
{
    OutputWrappedI(buf, start, end, RemainingWidth, bounds);
}


template <typename T>
inline void FTSimpleLayout::RenderSpaceI(const T *string, const int start,
                                         const int end, const float ExtraSpace)
{
    float space = 0.0;

    // If there is space to distribute, count the number of spaces
    if(ExtraSpace > 0.0)
    {
        int numSpaces = 0;

        // Count the number of space blocks in the input
        for(int i = start; ((end < 0) && string[i])
                              || ((end >= 0) && (i <= end)); i++)
        {
            // If this is the end of a space block, increment the counter
            if((i > start) && !isspace(string[i]) && isspace(string[i - 1]))
            {
                numSpaces++;
            }
        }

        space = ExtraSpace/numSpaces;
    }

    // Output all characters of the string
    for(int i = start; ((end < 0) && string[i])
                          || ((end >= 0) && (i <= end)); i++)
    {
        // If this is the end of a space block, distribute the extra space
        // inside it
        if((i > start) && !isspace(string[i]) && isspace(string[i - 1]))
        {
            pen += FTPoint(space, 0);
        }

        DoRender(currentFont, string[i], string[i + 1]);
    }
}


void FTSimpleLayout::RenderSpace(const char *string, const int start,
                                 const int end, const float ExtraSpace)
{
    RenderSpaceI(string, start, end, ExtraSpace);
}


void FTSimpleLayout::RenderSpace(const wchar_t *string, const int start,
                                 const int end, const float ExtraSpace)
{
    RenderSpaceI(string, start, end, ExtraSpace);
}

