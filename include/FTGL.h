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

#ifndef     __FTGL__
#define     __FTGL__

#ifdef __cplusplus
namespace FTGL
{
    typedef enum{RENDER_FRONT = 0x01, RENDER_BACK = 0x02, RENDER_SIDE = 0x04}ftglRenderMode;
    typedef enum{ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT, ALIGN_JUSTIFY} TextAlignment;
}
#else
#   define FTGL_RENDER_FRONT  0x01
#   define FTGL_RENDER_BACK   0x02
#   define FTGL_RENDER_SIDE   0x04
#   define FTGL_ALIGN_LEFT    0
#   define FTGL_ALIGN_CENTER  1
#   define FTGL_ALIGN_RIGHT   2
#   define FTGL_ALIGN_JUSTIFY 3
#endif

typedef double   FTGL_DOUBLE;
typedef float    FTGL_FLOAT;

// Fixes for deprecated identifiers in 2.1.5
#ifndef FT_OPEN_MEMORY
    #define FT_OPEN_MEMORY (FT_Open_Flags)1
#endif

#ifndef FT_RENDER_MODE_MONO
    #define FT_RENDER_MODE_MONO ft_render_mode_mono
#endif

#ifndef FT_RENDER_MODE_NORMAL
    #define FT_RENDER_MODE_NORMAL ft_render_mode_normal
#endif

  
#ifdef WIN32

    // Under windows avoid including <windows.h> is overrated. 
    // Sure, it can be avoided and "name space pollution" can be
    // avoided, but why? It really doesn't make that much difference
    // these days.
    #define  WIN32_LEAN_AND_MEAN
    #include <windows.h>

    #ifndef __gl_h_
        #include <GL/gl.h>
        #include <GL/glu.h>
    #endif

#else

    // Non windows platforms - don't require nonsense as seen above :-)
    #ifndef __gl_h_
        #ifdef SDL_main
            #include "SDL_opengl.h"
        #elif __APPLE_CC__
            #include <OpenGL/gl.h>
            #include <OpenGL/glu.h>
        #else
            #include <GL/gl.h>
            #if defined (__sun__) && !defined (__sparc__)
                #include <mesa/glu.h>
            #else
                #include <GL/glu.h>
            #endif
        #endif

    #endif

    // Required for compatibility with glext.h style function definitions of
    // OpenGL extensions, such as in src/osg/Point.cpp.
    #ifndef APIENTRY
        #define APIENTRY
    #endif
#endif

// Compiler-specific conditional compilation
#ifdef _MSC_VER // MS Visual C++ 

    // Disable various warning.
    // 4786: template name too long
    #pragma warning( disable : 4251 )
    #pragma warning( disable : 4275 )
    #pragma warning( disable : 4786 )

    // The following definitions control how symbols are exported.
    // If the target is a static library ensure that FTGL_LIBRARY_STATIC
    // is defined. If building a dynamic library (ie DLL) ensure the
    // FTGL_LIBRARY macro is defined, as it will mark symbols for 
    // export. If compiling a project to _use_ the _dynamic_ library 
    // version of the library, no definition is required. 
    #ifdef FTGL_LIBRARY_STATIC      // static lib - no special export required
    #  define FTGL_EXPORT
    #elif FTGL_LIBRARY              // dynamic lib - must export/import symbols appropriately.
    #  define FTGL_EXPORT   __declspec(dllexport)
    #else
    #  define FTGL_EXPORT   __declspec(dllimport)
    #endif 

#else
    // Compiler that is not MS Visual C++.
    // Ensure that the export symbol is defined (and blank)
    #define FTGL_EXPORT
#endif  

#endif  //  __FTGL__
