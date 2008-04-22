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

#include "FTTextureGlyph.h"

GLint FTTextureGlyph::activeTextureID = 0;

FTTextureGlyph::FTTextureGlyph(FT_GlyphSlot glyph, int id, int xOffset, int yOffset, GLsizei width, GLsizei height)
:   FTGlyph(glyph),
    destWidth(0),
    destHeight(0),
    glTextureID(id)
{
    err = FT_Render_Glyph(glyph, FT_RENDER_MODE_NORMAL);
    if(err || glyph->format != ft_glyph_format_bitmap)
    {
        return;
    }

    FT_Bitmap      bitmap = glyph->bitmap;

    destWidth  = bitmap.width;
    destHeight = bitmap.rows;

    if(destWidth && destHeight)
    {
        glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);
        glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glBindTexture(GL_TEXTURE_2D, glTextureID);
        glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, destWidth, destHeight, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap.buffer);

        glPopClientAttrib();
    }


//      0
//      +----+
//      |    |
//      |    |
//      |    |
//      +----+
//           1

    uv[0].X(static_cast<float>(xOffset) / static_cast<float>(width));
    uv[0].Y(static_cast<float>(yOffset) / static_cast<float>(height));
    uv[1].X(static_cast<float>(xOffset + destWidth) / static_cast<float>(width));
    uv[1].Y(static_cast<float>(yOffset + destHeight) / static_cast<float>(height));

    pos.X(glyph->bitmap_left);
    pos.Y(glyph->bitmap_top);
}


FTTextureGlyph::~FTTextureGlyph()
{}


const FTPoint& FTTextureGlyph::Render(const FTPoint& pen, int renderMode)
{
    if(activeTextureID != glTextureID)
    {
        glBindTexture(GL_TEXTURE_2D, (GLuint)glTextureID);
        activeTextureID = glTextureID;
    }

    glTranslatef(pen.X(),  pen.Y(), 0.0f);

    glBegin(GL_QUADS);
        glTexCoord2f(uv[0].X(), uv[0].Y());
        glVertex2f(pos.X(), pos.Y());

        glTexCoord2f(uv[0].X(), uv[1].Y());
        glVertex2f(pos.X(), pos.Y() - destHeight);

        glTexCoord2f(uv[1].X(), uv[1].Y());
        glVertex2f(destWidth + pos.X(), pos.Y() - destHeight);

        glTexCoord2f(uv[1].X(), uv[0].Y());
        glVertex2f(destWidth + pos.X(), pos.Y());
    glEnd();

    glTranslatef(-pen.X(), -pen.Y(), 0.0f);

    return advance;
}

