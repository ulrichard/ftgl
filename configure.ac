dnl Minimum version of autoconf required.  Should coincide with the
dnl setting in the autogen.sh script.
AC_PREREQ(2.58)

AC_INIT(FTGL, 2.1.3, [henryj@paradise.net.nz], ftgl)
AC_CONFIG_SRCDIR(src/FTPoint.cpp)
AC_CONFIG_AUX_DIR(.auto)
AM_INIT_AUTOMAKE([1.6 no-define dist-zip dist-bzip2])
AM_CONFIG_HEADER(config.h)

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
AM_PROG_CC_C_O

# Checks for header files.
AC_HEADER_STDC

# Checks for libraries.

AC_PATH_X

AC_CHECK_FT2([9.0.3],[],
             [AC_MSG_ERROR([FreeType2 is required to compile this library])])

AC_PATH_XTRA

FTGL_CHECK_GL
FTGL_CHECK_GLUT

AC_PATH_PROG(CPPUNIT, cppunit, no)
AM_CONDITIONAL(HAVE_CPPUNIT, test "x$CPPUNIT" != "xno")

# Checks for library functions -- this isn't really used at the moment
AC_CHECK_FUNCS([memset])

# Warning flags
CPPFLAGS="${CPPFLAGS} -Wall -Wpointer-arith -Wcast-align -Wcast-qual -Wshadow -Wsign-compare"
CFLAGS="${CFLAGS} -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs"

# Build HTML documentatin?
AC_PATH_PROG(DOXYGEN, doxygen, no)
AM_CONDITIONAL(HAVE_DOXYGEN, test "x$DOXYGEN" != "xno")

# Build PDF documentation?
AC_PATH_PROG(LATEX, pdflatex, no)
AC_PATH_PROG(KPSEWHICH, kpsewhich, no)
AC_PATH_PROG(DVIPS, dvips, no)
AC_PATH_PROG(EPSTOPDF, epstopdf, no)
if test "${DVIPS}" = "no" -o "${KPSEWHICH}" = "no" -o "${EPSTOPDF}" = "no"; then
  LATEX="no"
fi
if test "${LATEX}" != "no"; then
  AC_MSG_CHECKING(for a4.sty and a4wide.sty)
  if "${KPSEWHICH}" a4.sty >/dev/null 2>&1; then
    if "${KPSEWHICH}" a4wide.sty >/dev/null 2>&1; then
      AC_MSG_RESULT(yes)
    else
      LATEX="no"
      AC_MSG_RESULT(no)
    fi
  else
    LATEX="no"
    AC_MSG_RESULT(no)
  fi
fi
AM_CONDITIONAL(HAVE_LATEX, test "${LATEX}" != "no")

AC_CONFIG_FILES([
  ftgl.pc
])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  test/Makefile
  docs/Makefile
  docs/doxygen.cfg
  demo/Makefile
  msvc/Makefile
])
AC_OUTPUT

