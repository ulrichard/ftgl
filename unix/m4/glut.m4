dnl FTGL_CHECK_GLUT()
dnl Check for GLUT development environment
dnl
AC_DEFUN([FTGL_CHECK_GLUT],
[dnl
AC_CHECK_HEADER([GL/glut.h])
AC_CHECK_LIB(glut, [glutInit],
             [LIBGLUT=-lglut],
             [])

if test -z "${LIBGLUT}" ; then
    echo "Couldn't find GLUT, trying again with extra linker flags"
    unset ac_cv_lib_glut_glutInit
    AC_CHECK_LIB(glut, [glutInit],
                [LIBGLUT=-lglut],
                AC_MSG_ERROR([libglut is required to compile this library]),
                [-lX11])
fi
AC_SUBST(LIBGLUT)
])
