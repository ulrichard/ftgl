top_srcdir=../..
VPATH=$(top_srcdir)/demo
top_builddir=..
-include $(top_builddir)/Make.conf

TARGET = FTGLDemo

all: $(TARGET)

SRCS = \
	FTGLDemo.cpp			\
	tb.c				\
	trackball.c			\

HEADERS = \
	tb.h				\
	trackball.h			\

OBJS = $(patsubst %.cpp,%.$(OBJEXT),$(filter %.cpp,$(SRCS)))
OBJS += $(patsubst %.c,%.$(OBJEXT),$(filter %.c,$(SRCS)))

ALL_OBJS = $(OBJS)

CPPFLAGS += $(FT2_CFLAGS)
CPPFLAGS += -I$(top_srcdir)/src

LIBS += $(FT2_LIBS)

FTGLDemo: $(OBJS)
	$(LIBTOOL) --mode=link $(CC) $^ -o $@ $(top_builddir)/src/libftgl.la $(LIBGLUT)

install-local: FTGLDemo
	$(INSTALL) -d -m 0755 $(bindir)
	$(LIBTOOL) --mode=install $(INSTALL) -m 0755 $(TARGET) $(bindir)

clean-local:
	$(RM) $(ALL_OBJS)

distclean-local:
	$(RM) $(TARGET)
	$(RM) -r .libs

include $(top_builddir)/Make.rules
