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

#ifndef     __FTPoint__
#define     __FTPoint__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTGL.h"

/**
 * FTPoint class is a basic 3 dimensional point or vector.
 */
class FTGL_EXPORT FTPoint
{
    public:
        /**
         * Default constructor. Point is set to zero.
         */
        FTPoint()
        {
            values[0] = 0;
            values[1] = 0;
            values[2] = 0;
        }

        /**
         * Constructor. Z coordinate is set to zero if unspecified.
         *
         * @param x First component
         * @param y Second component
         * @param z Third component
         */
        FTPoint(const FTGL_DOUBLE x, const FTGL_DOUBLE y,
                const FTGL_DOUBLE z = 0)
        {
            values[0] = x;
            values[1] = y;
            values[2] = z;
        }

        /**
         * Constructor. This converts an FT_Vector to an FT_Point
         *
         * @param ft_vector A freetype vector
         */
        FTPoint(const FT_Vector& ft_vector)
        {
            values[0] = ft_vector.x;
            values[1] = ft_vector.y;
            values[2] = 0;
        }

        /**
         * Operator += In Place Addition.
         *
         * @param point
         * @return this plus point.
         */
        FTPoint& operator += (const FTPoint& point)
        {
            values[0] += point.values[0];
            values[1] += point.values[1];
            values[2] += point.values[2];

            return *this;
        }

        /**
         * Operator +
         *
         * @param point
         * @return this plus point.
         */
        FTPoint operator + (const FTPoint& point)
        {
            FTPoint temp;
            temp.values[0] = values[0] + point.values[0];
            temp.values[1] = values[1] + point.values[1];
            temp.values[2] = values[2] + point.values[2];

            return temp;
        }

         /**
         * Operator -= In Place Substraction.
         *
         * @param point
         * @return this minus point.
         */
        FTPoint& operator -= (const FTPoint& point)
        {
            values[0] -= point.values[0];
            values[1] -= point.values[1];
            values[2] -= point.values[2];

            return *this;
        }

        /**
         * Operator -
         *
         * @param point
         * @return this minus point.
         */
        FTPoint operator - (const FTPoint& point)
        {
            FTPoint temp;
            temp.values[0] = values[0] - point.values[0];
            temp.values[1] = values[1] - point.values[1];
            temp.values[2] = values[2] - point.values[2];

            return temp;
        }

        /**
         * Operator *
         *
         * @param multiplier
         * @return <code>this</code> multiplied by <code>multiplier</code>.
         */
        FTPoint operator * (double multiplier)
        {
            FTPoint temp;
            temp.values[0] = values[0] * multiplier;
            temp.values[1] = values[1] * multiplier;
            temp.values[2] = values[2] * multiplier;

            return temp;
        }


        /**
         * Operator *
         *
         * @param point
         * @param multiplier
         * @return <code>multiplier</code> multiplied by <code>point</code>.
         */
        friend FTPoint operator * (double multiplier, FTPoint& point);


        /**
         * Operator == Tests for eqaulity
         *
         * @param a
         * @param b
         * @return true if a & b are equal
         */
        friend bool operator == (const FTPoint &a, const FTPoint &b);

        /**
         * Operator != Tests for non equality
         *
         * @param a
         * @param b
         * @return true if a & b are not equal
         */
        friend bool operator != (const FTPoint &a, const FTPoint &b);


        /**
         * Cast to FTGL_DOUBLE*
         */
        operator const FTGL_DOUBLE*() const
        {
            return values;
        }


        /**
         * Setters
         */
        void X(FTGL_DOUBLE x) { values[0] = x; };
        void Y(FTGL_DOUBLE y) { values[1] = y; };
        void Z(FTGL_DOUBLE z) { values[2] = z; };


        /**
         * Getters
         */
        FTGL_DOUBLE X() const { return values[0]; };
        FTGL_DOUBLE Y() const { return values[1]; };
        FTGL_DOUBLE Z() const { return values[2]; };

    private:
        /**
         * The point data
         */
        FTGL_DOUBLE values[3];
};

#endif  //  __FTPoint__

