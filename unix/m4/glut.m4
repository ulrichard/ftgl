dnl FTGL_CHECK_GLUT()
dnl Check for GLUT development environment
dnl
AC_DEFUN([FTGL_CHECK_GLUT],
[dnl
AC_CHECK_HEADER([GL/glut.h])
AC_CHECK_LIB(glut, [glutInit],
             [LIBGLUT=-lglut],
             [])

# Work-arround for broken dynamic linkers and/or systems with non-broken
# linkers but suffering from PEBKAC.  The list of libraries is a bit
# over-generous, AFAIK -lXi is needed only on (some versions of?) SuSE

if test -z "${LIBGLUT}" ; then
    echo "Couldn't find GLUT, trying again with extra linker flags"
    unset ac_cv_lib_glut_glutInit
    AC_CHECK_LIB(glut, [glutInit],
                [LIBGLUT=-lglut],
                AC_MSG_ERROR([libglut is required to compile this library]),
                [-lX11 -lXmu -lXi -lm])
    LIBGLUT="$LIBGLUT -lX11 -lXmu -lXi -lm"
fi
AC_SUBST(LIBGLUT)
])
