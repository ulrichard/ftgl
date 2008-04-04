AC_INIT(ftgl, 2.0.5, henryj@paradise.net.nz)
AC_CONFIG_AUX_DIR(.auto)
AC_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE([no-define tar-ustar])

FTGL_PROG_CXX

AC_PROG_LIBTOOL

# Checks for typedefs, structures, and compiler characteristics.

dnl These don't mix with C++
dnl AC_C_CONST
dnl AC_C_INLINE

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADER([stdlib.h])

# Checks for libraries.

AC_PATH_X

AC_CHECK_FT2([9.0.3],[],
             [AC_MSG_ERROR([FreeType2 is required to compile this library])])

AC_PATH_XTRA

FTGL_CHECK_GL
FTGL_CHECK_GLUT

# Checks for library functions
dnl This isn't really used at the moment

AC_CHECK_FUNCS([memset])

# Utility programs

AC_PROG_INSTALL

AC_PATH_PROG(DOXYGEN, doxygen, no)
AM_CONDITIONAL(HAVE_DOXYGEN, test "$DOXYGEN" != "no")

AC_CONFIG_FILES([
  ftgl.pc
])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  docs/Makefile
  demo/Makefile
])
AC_OUTPUT

