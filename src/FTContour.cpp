/*
 * FTGL - OpenGL font library
 *
 * Copyright (c) 2001-2004 Henry Maddocks <ftgl@opengl.geek.nz>
 *               2008 Sam Hocevar <sam@zoy.org>
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

#include "FTContour.h"

static const float BEZIER_STEP_SIZE = 0.2f;


void FTContour::AddPoint(FTPoint point)
{
    if(pointList.empty() || point != pointList[pointList.size() - 1])
    {
        pointList.push_back(point);
    }
}


void FTContour::evaluateQuadraticCurve(FTPoint A, FTPoint B, FTPoint C)
{
    for(unsigned int i = 0; i <= (1.0f / BEZIER_STEP_SIZE); i++)
    {
        float t = static_cast<float>(i) * BEZIER_STEP_SIZE;

        FTPoint U = (1.0f - t) * A + t * B;
        FTPoint V = (1.0f - t) * B + t * C;

        AddPoint((1.0f - t) * U + t * V);
    }
}


void FTContour::evaluateCubicCurve(FTPoint A, FTPoint B, FTPoint C, FTPoint D)
{
    for(unsigned int i = 0; i <= (1.0f / BEZIER_STEP_SIZE); i++)
    {
        float t = static_cast<float>(i) * BEZIER_STEP_SIZE;

        FTPoint U = (1.0f - t) * A + t * B;
        FTPoint V = (1.0f - t) * B + t * C;
        FTPoint W = (1.0f - t) * C + t * D;

        FTPoint M = (1.0f - t) * U + t * V;
        FTPoint N = (1.0f - t) * V + t * W;

        AddPoint((1.0f - t) * M + t * N);
    }
}


FTContour::FTContour(FT_Vector* contour, char* tags, unsigned int n)
{
    for(unsigned int i = 0; i < n; ++ i)
    {
        if(tags[i] == FT_Curve_Tag_On || n < 2)
        {
            AddPoint(contour[i]);
            continue;
        }

        FTPoint cur(contour[i]);
        FTPoint prev = (0 == i)
                       ? FTPoint(contour[n - 1])
                       : pointList[pointList.size() - 1];

        FTPoint next = (i == n - 1)
                       ? pointList[0]
                       : FTPoint(contour[i + 1]);

        if(tags[i] == FT_Curve_Tag_Conic)
        {
            while(tags[(i == n - 1) ? 0 : i + 1] == FT_Curve_Tag_Conic)
            {
                next = (cur + next) * 0.5f;

                evaluateQuadraticCurve(prev, cur, next);
                ++i;

                prev = next;
                cur = FTPoint(contour[i]);
                next = (i == n - 1)
                       ? pointList[0]
                       : FTPoint(contour[i + 1]);
            }

            evaluateQuadraticCurve(prev, cur, next);
            continue;
        }

        if(tags[i] == FT_Curve_Tag_Cubic)
        {
            FTPoint cur2 = next;

            FTPoint next = (i == n - 2)
                           ? pointList[0]
                           : FTPoint(contour[i + 2]);

            evaluateCubicCurve(prev, cur, cur2, next);
            ++i;
            continue;
        }
    }
}

