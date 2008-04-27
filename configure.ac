AC_INIT(ftgl, 2.1.3, henryj@paradise.net.nz)
AC_CONFIG_AUX_DIR(.auto)
AC_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE([no-define tar-ustar])

FTGL_PROG_CXX

LT_MAJOR="2"
LT_MINOR="1"
LT_MICRO="3"
AC_SUBST(LT_MAJOR)
AC_SUBST(LT_MINOR)
AC_SUBST(LT_MICRO)
LT_VERSION="$LT_MAJOR:$LT_MINOR:$LT_MICRO"
AC_SUBST(LT_VERSION)

AC_PROG_LIBTOOL
AC_PROG_INSTALL

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

CPPUNIT="no"
PKG_CHECK_MODULES(CPPUNIT, cppunit, [CPPUNIT="yes"], [AC_MSG_RESULT(no)])
AM_CONDITIONAL(HAVE_CPPUNIT, test "$CPPUNIT" != "no")

# Checks for library functions -- this isn't really used at the moment
AC_CHECK_FUNCS([memset])

# Warning flags
CPPFLAGS="${CPPFLAGS} -Wall -Wpointer-arith -Wcast-align -Wcast-qual -Wshadow -Wsign-compare"
CFLAGS="${CFLAGS} -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs"

# Utility programs
AC_PATH_PROG(DOXYGEN, doxygen, no)
AM_CONDITIONAL(HAVE_DOXYGEN, test "$DOXYGEN" != "no")

AC_CONFIG_FILES([
  ftgl.pc
])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  test/Makefile
  docs/Makefile
  demo/Makefile
  msvc/Makefile
])
AC_OUTPUT

