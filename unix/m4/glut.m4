dnl FTGL_CHECK_GL()
dnl Check for OpenGL development environment and GLU >= 1.2
dnl
AC_DEFUN([FTGL_CHECK_GLUT],
[dnl
AC_CHECK_HEADER([GL/glut.h])
AC_CHECK_LIB(glut, [glutInit],
             [LIBGLUT=-lglut],
             [AC_MSG_ERROR([libglut is required to compile this library])])
AC_SUBST(LIBGLUT)
])
