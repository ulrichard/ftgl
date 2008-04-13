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


FTSimpleLayout::FTSimpleLayout() {
   currentFont = NULL;
   lineLength = 100.0f;
   alignment = ALIGN_LEFT;
   lineSpacing = 1.0f;
} /* FTSimpleLayout::FTSimpleLayout() */

void FTSimpleLayout::BBox(const char *String,float& llx, float& lly, float& llz, float& urx, float& ury, float& urz) {
   FTBBox bounds; 
   
   WrapText(String,&bounds); 
   llx = bounds.lowerX; lly = bounds.lowerY; llz = bounds.lowerZ;
   urx = bounds.upperX; ury = bounds.upperY; urz = bounds.upperZ;
} /* FTSimpleLayout::BBox() */

void FTSimpleLayout::BBox(const wchar_t *String,float& llx, float& lly, float& llz, float& urx, float& ury, float& urz) {
   FTBBox bounds; 
   
   WrapText(String,&bounds); 
   llx = bounds.lowerX; lly = bounds.lowerY; llz = bounds.lowerZ;
   urx = bounds.upperX; ury = bounds.upperY; urz = bounds.upperZ;
} /* FTSimpleLayout::BBox() */

void FTSimpleLayout::Render(const char *String) {
   pen.X(0.0f); pen.Y(0.0f);
   WrapText(String,NULL);
} /* FTSimpleLayout::Render() */

void FTSimpleLayout::Render(const wchar_t* String) {
   pen.X(0.0f); pen.Y(0.0f);
   WrapText(String,NULL);
} /* FTSimpleLayout::Render() */

void FTSimpleLayout::WrapText(const char *Buffer,FTBBox *bounds) {
   int breakIdx = 0;          // The index of the last break character
   int lineStart = 0;         // The character index of the line start
   float nextStart = 0.0;     // The total width of the line being generated
   float breakWidth = 0.0;    // The width of the line up to the last word break
   float currentWidth = 0.0;  // The width of all characters on the line being generated
   float prevWidth;           // The width of all characters but the current glyph
   float wordLength = 0.0;    // The length of the block since the last break character
   float glyphWidth,advance;
   FTBBox glyphBounds;
   /* Reset the pen position */
   pen.Y(0);
   
   if (bounds) {
      bounds->Invalidate();
   } /* If we have bounds mark them invalid (if bounds) */
   
   for (int charIdx = 0;Buffer[charIdx];charIdx++) {         
      /* Find the width of the current glyph */
      CheckGlyph(currentFont,Buffer[charIdx]);
      glyphBounds = GetGlyphs(currentFont)->BBox(Buffer[charIdx]);
      glyphWidth = glyphBounds.upperX - glyphBounds.lowerX;
      
      advance = GetGlyphs(currentFont)->Advance(Buffer[charIdx],Buffer[charIdx + 1]);
      prevWidth = currentWidth;
      /* Compute the width of all glyphs up to the end of Buffer[charIdx] */
      currentWidth = nextStart + glyphWidth;
      /* Compute the position of the next glyph */
      nextStart += advance;
      
      if ((currentWidth > lineLength) || (Buffer[charIdx] == '\n')) {
         /* A non whitespace character has exceeded the line length.  Or a */
         /* newline character has forced a line break.  Output the last    */
         /* line and start a new line after the break character.           */
         
         if (!breakIdx || (Buffer[charIdx] == '\n')) {
            /* Break on the previous character */
            breakIdx = charIdx - 1;
            breakWidth = prevWidth;
            /* None of the previous word will be carried to the next line */
            wordLength = 0;
            /* If the current character is a newline discard it's advance */
            if (Buffer[charIdx] == '\n') advance = 0;
         } /* If we have not yet found a break break on the last character (if !breakIdx) */
         
         float remainingWidth = lineLength - breakWidth;

         /* Render the current substring */
         if (Buffer[breakIdx + 1] == '\n') {
            breakIdx++;
            OutputWrapped(Buffer,lineStart,breakIdx -1,remainingWidth,bounds);
         } else {
            OutputWrapped(Buffer,lineStart,breakIdx   ,remainingWidth,bounds);
         } /* If the break character is a newline do not render it (if Buffer[charIdx]) */

         /* Store the start of the next line */
         lineStart = breakIdx + 1;
         // TODO: Is Height() the right value here?
         pen.Y(pen.Y() - GetCharSize(currentFont).Height()*lineSpacing);
         /* The current width is the width since the last break */
         nextStart = wordLength + advance;
         wordLength += advance;
         currentWidth = wordLength + advance;
         /* Reset the safe break for the next line */
         breakIdx = 0;
      } else if (isspace(Buffer[charIdx])) {
         /* This is the last word break position */
         wordLength = 0;
         breakIdx = charIdx;

         if (!charIdx || !isspace(Buffer[charIdx - 1])) {
            /* Record the width of the start of the block */
            breakWidth = currentWidth;
         } /* Check to see if this is the first whitespace character in a run (if !isspace()) */
      } else {
         wordLength += advance;
      } /* See if Buffer[charIdx] is a space, a break or a regular charactger (if/elseif/else Buffer[]) */
   } /* Scan the input for all characters that need output (for charIdx) */
   
   float remainingWidth = lineLength - currentWidth;
   /* Render any remaining text on the last line */
   if (alignment == ALIGN_JUST) {
      alignment = ALIGN_LEFT;
      OutputWrapped(Buffer,lineStart,-1,remainingWidth,bounds);
      alignment = ALIGN_JUST;
   } else {
      OutputWrapped(Buffer,lineStart,-1,remainingWidth,bounds);
   } /* Disable justification for the last row (if/else Alignemnt) */
} /* FTSimpleLayout::WrapText() */

void FTSimpleLayout::WrapText(const wchar_t* Buffer,FTBBox *bounds) {
   int breakIdx = 0;           // The index of the last break character
   int lineStart = 0;          // The character index of the line start
   float nextStart = 0.0f;     // The total width of the line being generated
   float breakWidth = 0.0f;    // The width of the line up to the last word break
   float currentWidth = 0.0f;  // The width of all characters on the line being generated
   float prevWidth;            // The width of all characters but the current glyph
   float wordLength = 0.0f;    // The length of the block since the last break character
   float glyphWidth,advance;
   FTBBox glyphBounds;
   /* Reset the pen position */
   pen.Y(0);
   
   if (bounds) {
      bounds->Invalidate();
   } /* If we have bounds mark them invalid (if bounds) */
   
   for (int charIdx = 0;Buffer[charIdx];charIdx++) {         
      /* Find the width of the current glyph */
      CheckGlyph(currentFont,Buffer[charIdx]);
      glyphBounds = GetGlyphs(currentFont)->BBox(Buffer[charIdx]);
      glyphWidth = glyphBounds.upperX - glyphBounds.lowerX;
      
      advance = GetGlyphs(currentFont)->Advance(Buffer[charIdx],Buffer[charIdx + 1]);
      prevWidth = currentWidth;
      /* Compute the width of all glyphs up to the end of Buffer[charIdx] */
      currentWidth = nextStart + glyphWidth;
      /* Compute the position of the next glyph */
      nextStart += advance;
      
      if ((currentWidth > lineLength) || (Buffer[charIdx] == '\n')) {
         /* A non whitespace character has exceeded the line length.  Or a */
         /* newline character has forced a line break.  Output the last    */
         /* line and start a new line after the break character.           */
         
         if (!breakIdx || (Buffer[charIdx] == '\n')) {
            /* Break on the previous character */
            breakIdx = charIdx - 1;
            breakWidth = prevWidth;
            /* None of the previous word will be carried to the next line */
            wordLength = 0;
            /* If the current character is a newline discard it's advance */
            if (Buffer[charIdx] == '\n') advance = 0;
         } /* If we have not yet found a break break on the last character (if !breakIdx) */
         
         float remainingWidth = lineLength - breakWidth;

         /* Render the current substring */
         if (Buffer[breakIdx + 1] == '\n') {
            breakIdx++;
            OutputWrapped(Buffer,lineStart,breakIdx -1,remainingWidth,bounds);
         } else {
            OutputWrapped(Buffer,lineStart,breakIdx   ,remainingWidth,bounds);
         } /* If the break character is a newline do not render it (if Buffer[charIdx]) */

         /* Store the start of the next line */
         lineStart = breakIdx + 1;
         // TODO: Is Height() the right value here?
         pen.Y(pen.Y() - GetCharSize(currentFont).Height()*lineSpacing);
         /* The current width is the width since the last break */
         nextStart = wordLength + advance;
         wordLength += advance;
         currentWidth = wordLength + advance;
         /* Reset the safe break for the next line */
         breakIdx = 0;
      } else if (isspace(Buffer[charIdx])) {
         /* This is the last word break position */
         wordLength = 0;
         breakIdx = charIdx;

         if (!charIdx || !isspace(Buffer[charIdx - 1])) {
            /* Record the width of the start of the block */
            breakWidth = currentWidth;
         } /* Check to see if this is the first whitespace character in a run (if !isspace()) */
      } else {
         wordLength += advance;
      } /* See if Buffer[charIdx] is a space, a break or a regular charactger (if/elseif/else Buffer[]) */
   } /* Scan the input for all characters that need output (for charIdx) */
   
   float remainingWidth = lineLength - currentWidth;
   /* Render any remaining text on the last line */
   if (alignment == ALIGN_JUST) {
      alignment = ALIGN_LEFT;
      OutputWrapped(Buffer,lineStart,-1,remainingWidth,bounds);
      alignment = ALIGN_JUST;
   } else {
      OutputWrapped(Buffer,lineStart,-1,remainingWidth,bounds);
   } /* Disable justification for the last row (if/else Alignemnt) */
} /* FTSimpleLayout::WrapText() */

void FTSimpleLayout::OutputWrapped(const char *Buffer,const int StartIdx,const int EndIdx,const float RemainingWidth,FTBBox *bounds) {
   float distributeWidth = 0.0;
   switch (alignment) {
      case ALIGN_LEFT:
         pen.X(0);
         break;
      case ALIGN_CENTER:
         pen.X(RemainingWidth/2);
         break;
      case ALIGN_RIGHT:
         pen.X(RemainingWidth);
         break;
      case ALIGN_JUST:
         pen.X(0);
         distributeWidth = RemainingWidth;
         break;
   } /* Allign the text according as specified by Alignment (switch Alignment) */

   if (bounds) {
      float llx,lly,llz,urx,ury,urz;
      currentFont->BBox(Buffer,StartIdx,EndIdx,llx,lly,llz,urx,ury,urz);

      /* Add the extra space to the upper x dimension */
      urx += distributeWidth;
      // TODO: It's a little silly to convert from a FTBBox to floats and back again, but I don't want to 
      //       implement yet another method for finding the bounding box as a BBox.
      FTBBox temp(llx,lly,llz,urx,ury,urz);
      temp.Move(FTPoint(pen.X(), pen.Y(), 0.0f));
      
      if (!bounds->IsValid()) {
         *bounds = temp;
      } else {
         *bounds += temp;
      } /* See if this is the first area to be added to the bounds (if/else bounds) */
   } else {
      RenderSpace(Buffer,StartIdx,EndIdx,distributeWidth);
   } /* If we have bounds expand them by the lines bounds, otherwise render the line (if/else bounds) */
} /* FTSimpleLayout::OutputWrapped() */

void FTSimpleLayout::OutputWrapped(const wchar_t *Buffer,const int StartIdx,const int EndIdx,const float RemainingWidth,FTBBox *bounds) {
   float distributeWidth = 0.0;
   switch (alignment) {
      case ALIGN_LEFT:
         pen.X(0); 
         break;
      case ALIGN_CENTER:
         pen.X(RemainingWidth/2);
         break;
      case ALIGN_RIGHT:
         pen.X(RemainingWidth);
         break;
      case ALIGN_JUST:
         pen.X(0);
         distributeWidth = RemainingWidth;
         break;
   } /* Allign the text according as specified by Alignment (switch Alignment) */

   if (bounds) {
      float llx,lly,llz,urx,ury,urz;
      currentFont->BBox(Buffer,StartIdx,EndIdx,llx,lly,llz,urx,ury,urz);

      /* Add the extra space to the upper x dimension */
      urx += distributeWidth;
      // TODO: It's a little silly to convert from a FTBBox to floats and back again, but I don't want to 
      //       implement yet another method for finding the bounding box as a BBox.
      FTBBox temp(llx,lly,llz,urx,ury,urz);
      temp.Move(FTPoint(pen.X(), pen.Y(), 0.0f));
      
      if (!bounds->IsValid()) {
         *bounds = temp;
      } else {
         *bounds += temp;
      } /* See if this is the first area to be added to the bounds (if/else bounds) */
   } else {
      RenderSpace(Buffer,StartIdx,EndIdx,distributeWidth);
   } /* If we have bounds expand them by the lines bounds, otherwise render the line (if/else bounds) */
} /* FTSimpleLayout::OutputWrapped() */

void FTSimpleLayout::RenderSpace(const char *String,const int StartIdx,const int EndIdx,const float ExtraSpace) {
   float space = 0.0;
   
   if (ExtraSpace > 0.0) {
      int numSpaces = 0;

      for (int idx = StartIdx;((EndIdx < 0) && String[idx]) || ((EndIdx >= 0) && (idx <= EndIdx));idx++) {
         if ((idx > StartIdx) && !isspace(String[idx]) && isspace(String[idx - 1])) {
            numSpaces++;
         } /* If this is the end of a space block increment the counter (if isspace()) */
      } /* Count the number of space blocks in the input (for idx) */
      
      space = ExtraSpace/numSpaces;
   } /* If there is space to distribute count the number of spaces (if ExtraSpace) */
   
   for (int idx = StartIdx;((EndIdx < 0) && String[idx]) || ((EndIdx >= 0) && (idx <= EndIdx));idx++) {
      if ((idx > StartIdx) && !isspace(String[idx]) && isspace(String[idx - 1])) {
         pen.X(pen.X() + space);
      } /* If this is the end of a space block distribute the extra space into it (if isspace()) */

      DoRender(currentFont,String[idx],String[idx + 1]);
   } /* Output all characters of the string (for idx) */
} /* FTSimpleLayout::RenderSpace() */

void FTSimpleLayout::RenderSpace(const wchar_t *String,const int StartIdx,const int EndIdx,const float ExtraSpace) {
   float space = 0.0;
   
   if (ExtraSpace > 0.0) {
      int numSpaces = 0;

      for (int idx = StartIdx;((EndIdx < 0) && String[idx]) || ((EndIdx >= 0) && (idx <= EndIdx));idx++) {
         if ((idx > StartIdx) && !isspace(String[idx]) && isspace(String[idx - 1])) {
            numSpaces++;
         } /* If this is the end of a space block increment the counter (if isspace()) */
      } /* Count the number of space blocks in the input (for idx) */
      
      space = ExtraSpace/numSpaces;
   } /* If there is space to distribute count the number of spaces (if ExtraSpace) */
   
   for (int idx = StartIdx;((EndIdx < 0) && String[idx]) || ((EndIdx >= 0) && (idx <= EndIdx));idx++) {
      if ((idx > StartIdx) && !isspace(String[idx]) && isspace(String[idx - 1])) {
         pen.X(pen.X() + space);
      } /* If this is the end of a space block distribute the extra space into it (if isspace()) */

      DoRender(currentFont,String[idx],String[idx + 1]);
   } /* Output all characters of the string (for idx) */
} /* FTSimpleLayout::RenderSpace() */
