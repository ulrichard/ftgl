FTGL Version 1.4

This project will build a static library (archive) in the src directory.

The Makefiles need GNU Make in order to work properly.

FTGL requires the Freetype2 library (version 2.0.9 or later) and OpenGL
(glu version 1.2 or later). You can pass flags to the configure script
to point it to the place where these libraries are installed.
Optionally, if doxygen is installed, documentation in HTML format will
be generated in the docs subdirectory.

To use FTGL in your own projects you will need to link against this lib
and include the FTGL headers located in the src directory. Your project
will also need Freetype and OpenGL.  For your convinience a pkg-config
metadata file has been included (ftgl.pc) and gets installed in
<libdir>/pkgconfig, where pkg-config should be able to find it.  In
order to take advantage of this, just include something like this in
your makefiles:

    FTGL_CPPFLAGS := $(shell pkg-config --cflags ftgl)
    FTGL_LDFLAGS  := $(shell pkg-config --libs-only-L ftgl)
    FTGL_LIBS     := $(shell pkg-config --libs-only-l ftgl)

The names of these variables should be self-explanatory.  Note that
FTGL_LIBS will include -lGL, you shouldn't specify that flag separately.

For instructions on using Freetype go to http://www.freetype.org/
For instructions on using OpenGL go to http://www.opengl.org/

Please contact me if you have any suggestions, feature requests, or
problems.

Henry Maddocks
henryj@paradise.net.nz
http://homepages.paradise.net.nz/henryj/
