dnl FTGL_CHECK_GL()
dnl Check for OpenGL development environment and GLU >= 1.2
dnl
AC_DEFUN([FTGL_CHECK_GL],
[dnl
AC_CHECK_HEADER([GL/gl.h])
AC_CHECK_LIB(GL, [glBegin], [],
    [AC_MSG_NOTICE([GL not found in the compiler's path, looking in the X11 tree])
     unset ac_cv_lib_GL_glBegin
     LDFLAGS="-L${x_libraries} $LDFLAGS"
     AC_CHECK_LIB(GL, [glBegin], [],
         [AC_MSG_ERROR([libGL is required to compile this library])])
    ])

AC_CHECK_HEADER([GL/glu.h])
AC_MSG_CHECKING([for GLU version >= 1.2])
AC_TRY_COMPILE([#include <GL/glu.h>], [
#if !defined(GLU_VERSION_1_2)
#error GLU too old
#endif
               ],
               [AC_MSG_RESULT([yes])],
               [AC_MSG_RESULT([no])
                AC_MSG_ERROR([GLU >= 1.2 is needed to compile this library])
               ])
AC_CHECK_LIB(GLU, [gluNewTess],
             [], [AC_MSG_ERROR([libGLU is required to compile this library])])
])
