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

#include "config.h"

#include <math.h>

#include "ftgl.h"
#include "FTPoint.h"

bool operator == (const FTPoint &a, const FTPoint &b)
{
    return((a.values[0] == b.values[0]) && (a.values[1] == b.values[1]) && (a.values[2] == b.values[2]));
}

bool operator != (const FTPoint &a, const FTPoint &b)
{
    return((a.values[0] != b.values[0]) || (a.values[1] != b.values[1]) || (a.values[2] != b.values[2]));
}


FTPoint operator*(double multiplier, FTPoint& point)
{
    return point * multiplier;
}

FTPoint FTPoint::GetNormal(const FTPoint &a, const FTPoint &b)
{
    float vectorX = a.X() - b.X();
    float vectorY = a.Y() - b.Y();

    float length = sqrt(vectorX * vectorX + vectorY * vectorY);

    if(length > 0.01f)
    {
        length = 1 / length;
    }
    else
    {
        length = 0.0f;
    }

    return FTPoint(-vectorY * length,
                    vectorX * length,
                    0.0f);
}

