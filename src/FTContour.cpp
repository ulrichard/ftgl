/*
 * FTGL - OpenGL font library
 *
 * Copyright (c) 2001-2004 Henry Maddocks <ftgl@opengl.geek.nz>
 *               2008 Sam Hocevar <sam@zoy.org>
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
 */

#include "config.h"

#include "FTContour.h"

#include <math.h>

static const unsigned int BEZIER_STEPS = 5;


void FTContour::AddPoint(FTPoint point)
{
    if(pointList.empty() || (point != pointList[pointList.size() - 1]
                              && point != pointList[0]))
    {
        pointList.push_back(point);
    }
}


void FTContour::AddOutsetPoint(FTPoint point)
{
    outsetPointList.push_back(point);
}


void FTContour::AddFrontPoint(FTPoint point)
{
    frontPointList.push_back(point);
}


void FTContour::AddBackPoint(FTPoint point)
{
    backPointList.push_back(point);
}


void FTContour::evaluateQuadraticCurve(FTPoint A, FTPoint B, FTPoint C)
{
    for(unsigned int i = 1; i < BEZIER_STEPS; i++)
    {
        float t = static_cast<float>(i) / BEZIER_STEPS;

        FTPoint U = (1.0f - t) * A + t * B;
        FTPoint V = (1.0f - t) * B + t * C;

        AddPoint((1.0f - t) * U + t * V);
    }
}


void FTContour::evaluateCubicCurve(FTPoint A, FTPoint B, FTPoint C, FTPoint D)
{
    for(unsigned int i = 0; i < BEZIER_STEPS; i++)
    {
        float t = static_cast<float>(i) / BEZIER_STEPS;

        FTPoint U = (1.0f - t) * A + t * B;
        FTPoint V = (1.0f - t) * B + t * C;
        FTPoint W = (1.0f - t) * C + t * D;

        FTPoint M = (1.0f - t) * U + t * V;
        FTPoint N = (1.0f - t) * V + t * W;

        AddPoint((1.0f - t) * M + t * N);
    }
}

FTGL_DOUBLE FTContour::NormVector(const FTPoint &v)
{
    return sqrt(v.X() * v.X() + v.Y() * v.Y());
}

void FTContour::RotationMatrix(const FTPoint &a, const FTPoint &b, FTGL_DOUBLE *matRot, FTGL_DOUBLE *invRot)
{
    FTPoint abVect(b.X() - a.X(), b.Y() - a.Y(), 0);
    FTGL_DOUBLE abNorm = NormVector(abVect);
    invRot[0] = matRot[0] = -abVect.X() / abNorm;
    invRot[2] = matRot[1] = -abVect.Y() / abNorm;
    invRot[1] = matRot[2] =  abVect.Y() / abNorm;
    invRot[3] = matRot[3] = -abVect.X() / abNorm;
}

void FTContour::MultMatrixVect(FTGL_DOUBLE *mat, FTPoint &v)
{
    FTPoint res;
    res.X(v.X() * mat[0] + v.Y() * mat[1]);
    res.Y(v.X() * mat[2] + v.Y() * mat[3]);
    v.X(res.X());
    v.Y(res.Y());
}

void FTContour::ComputeBisec(FTPoint &v)
{
    FTGL_DOUBLE sgn = -64.0;
    if((v.Y() / NormVector(v)) < 0)
        sgn = 64.0;
    v.X(sgn * sqrt((NormVector(v) - v.X()) / (NormVector(v) + v.X())));
    v.Y(64.0);
}

FTPoint FTContour::ComputeOutsetPoint(FTPoint a, FTPoint b, FTPoint c)
{
    FTGL_DOUBLE mat[4], inv[4];
    /* Build the rotation matrix from 'ab' vector */
    RotationMatrix(b, a, mat, inv);
    /* 'h' is the second vector 'bc' */
    FTPoint h = c - b;
    /* Apply the rotation to the second vector 'bc' */
    MultMatrixVect(mat, h);
    /* Compute the vector bisecting 'bh' */
    ComputeBisec(h);
    /* Apply the inverted rotation matrix to 'bh' */
    MultMatrixVect(inv, h);
    return h;
}

void FTContour::outsetContour()
{
    size_t size = PointCount();
    FTPoint vOutset;
    for(unsigned int pointIndex = 0; pointIndex < size; ++pointIndex)
    {
        int prev = (pointIndex%size + size - 1) % size;
        int cur = pointIndex%size;
        int next = (pointIndex%size + 1) % size;
        /* Build the outset shape with d = 1.0f */
        vOutset = ComputeOutsetPoint(Point(prev), Point(cur), Point(next));
        AddOutsetPoint(vOutset);
    }
}


FTContour::FTContour(FT_Vector* contour, char* tags, unsigned int n)
{
    // See http://freetype.sourceforge.net/freetype2/docs/glyphs/glyphs-6.html
    // for a full description of FreeType tags.
    for(unsigned int i = 0; i < n; i++)
    {
        FTPoint cur(contour[i]);

        // Only process point tags we know.
        if(n < 2 || FT_CURVE_TAG(tags[i]) == FT_Curve_Tag_On)
        {
            AddPoint(cur);
        }
        else if(FT_CURVE_TAG(tags[i]) == FT_Curve_Tag_Conic)
        {
            // Previous point is either the real previous point (an "on"
            // point), or the midpoint between the current one and the
            // previous "conic off" point.
            FTPoint prev(contour[(i - 1 + n) % n]);
            if(FT_CURVE_TAG(tags[(i - 1 + n) % n]) == FT_Curve_Tag_Conic)
            {
                prev = (cur + prev) * 0.5;
                AddPoint(prev);
            }

            // Next point is either the real next point or the midpoint.
            FTPoint next(contour[(i + 1) % n]);
            if(FT_CURVE_TAG(tags[(i + 1) % n]) == FT_Curve_Tag_Conic)
            {
                next = (cur + next) * 0.5;
            }

            evaluateQuadraticCurve(prev, cur, next);
        }
        else if(FT_CURVE_TAG(tags[i]) == FT_Curve_Tag_Cubic
                 && FT_CURVE_TAG(tags[(i + 1) % n]) == FT_Curve_Tag_Cubic)
        {
            evaluateCubicCurve(FTPoint(contour[(i - 1 + n) % n]),
                               cur,
                               FTPoint(contour[(i + 1) % n]),
                               FTPoint(contour[(i + 2) % n]));
        }
    }

    /* Create (or not) front outset and/or back outset */
    outsetContour();
}


void FTContour::buildFrontOutset(float outset)
{
    for(size_t i = 0; i < PointCount(); ++i)
    {
        FTPoint point = FTPoint(Point(i).X() + Outset(i).X() * outset,
                                Point(i).Y() + Outset(i).Y() * outset,
                                0);
       AddFrontPoint(point);
    }
}
void FTContour::buildBackOutset(float outset)
{
    for(size_t i = 0; i < PointCount(); ++i)
    {
        FTPoint point = FTPoint(Point(i).X() + Outset(i).X() * outset,
                                Point(i).Y() + Outset(i).Y() * outset,
                                0);
       AddBackPoint(point);
    }
}

