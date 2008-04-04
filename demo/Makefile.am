
if HAVE_GLUT
noinst_PROGRAMS = FTGLDemo
endif

FTGLDemo_SOURCES = \
	FTGLDemo.cpp \
	tb.c \
	tb.h \
	trackball.c \
	trackball.h \
	$(NULL)
FTGLDemo_CPPFLAGS = -I$(top_srcdir)/include
FTGLDemo_CXXFLAGS = $(FT2_CFLAGS) $(GL_CFLAGS)
FTGLDemo_LDFLAGS = $(FT2_LIBS) $(GLUT_LIBS)
FTGLDemo_LDADD = ../src/libftgl.la

