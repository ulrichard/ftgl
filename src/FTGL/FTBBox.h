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

#ifndef __FTBBox__
#define __FTBBox__

#ifdef __cplusplus


/**
 * FTBBox is a convenience class for handling bounding boxes.
 */
class FTGL_EXPORT FTBBox
{
    public:
        /**
         * Default constructor. Bounding box is set to zero.
         */
        FTBBox()
        :   lowerX(0.0f),
            lowerY(0.0f),
            lowerZ(0.0f),
            upperX(0.0f),
            upperY(0.0f),
            upperZ(0.0f)
        {}

        /**
         * Constructor.
         */
        FTBBox(float lx, float ly, float lz, float ux, float uy, float uz)
        :   lowerX(lx),
            lowerY(ly),
            lowerZ(lz),
            upperX(ux),
            upperY(uy),
            upperZ(uz)
        {}

        /**
         * Constructor. Extracts a bounding box from a freetype glyph. Uses
         * the control box for the glyph. <code>FT_Glyph_Get_CBox()</code>
         *
         * @param glyph A freetype glyph
         */
        FTBBox(FT_GlyphSlot glyph)
        :   lowerX(0.0f),
            lowerY(0.0f),
            lowerZ(0.0f),
            upperX(0.0f),
            upperY(0.0f),
            upperZ(0.0f)
        {
            FT_BBox bbox;
            FT_Outline_Get_CBox(&(glyph->outline), &bbox);

            lowerX = static_cast<float>(bbox.xMin) / 64.0f;
            lowerY = static_cast<float>(bbox.yMin) / 64.0f;
            lowerZ = 0.0f;
            upperX = static_cast<float>(bbox.xMax) / 64.0f;
            upperY = static_cast<float>(bbox.yMax) / 64.0f;
            upperZ = 0.0f;

        }

        /**
         * Destructor
         */
        ~FTBBox()
        {}

        /**
         * Mark the bounds invalid by setting all lower dimensions greater
         * than the upper dimensions.
         */
        void Invalidate()
        {
            lowerX = lowerY = lowerZ = 1.0f;
            upperX = upperY = upperZ = -1.0f;
        }

        /**
         * Determines if this bounding box is valid.
         *
         * @return True if all lower values are <= the corresponding
         *         upper values.
         */
        bool IsValid()
        {
            return((lowerX <= upperX) && (lowerY <= upperY) && (lowerZ <= upperZ));
        }

        /**
         * Move the Bounding Box by a vector.
         *
         * @param distance The distance to move the bbox in 3D space.
         */
        FTBBox& Move(FTPoint distance)
        {
            lowerX += distance.X();
            lowerY += distance.Y();
            lowerZ += distance.Z();
            upperX += distance.X();
            upperY += distance.Y();
            upperZ += distance.Z();
            return *this;
        }

        FTBBox& operator += (const FTBBox& bbox)
        {
            lowerX = bbox.lowerX < lowerX? bbox.lowerX: lowerX;
            lowerY = bbox.lowerY < lowerY? bbox.lowerY: lowerY;
            lowerZ = bbox.lowerZ < lowerZ? bbox.lowerZ: lowerZ;
            upperX = bbox.upperX > upperX? bbox.upperX: upperX;
            upperY = bbox.upperY > upperY? bbox.upperY: upperY;
            upperZ = bbox.upperZ > upperZ? bbox.upperZ: upperZ;

            return *this;
        }

        void SetDepth(float depth)
        {
            upperZ = lowerZ + depth;
        }


        /**
         * The bounds of the box
         */
        // Make these ftPoints & private
        float lowerX, lowerY, lowerZ, upperX, upperY, upperZ;
    protected:


    private:

};

#endif //__cplusplus

#endif  //  __FTBBox__

