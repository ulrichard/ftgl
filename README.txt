FTGL 1.3b3
November 13 2001

DESCRIPTION:

FTGL is a free open source library to enable developers to use arbitrary
fonts in their OpenGL (www.opengl.org)  applications.
Unlike other OpenGL font libraries FTGL uses standard font file formats
so doesn't need a preprocessing step to convert the high quality font data
into a lesser quality, proprietary format.
FTGL uses the Freetype (www.freetype.org) font library to open and 'decode'
the fonts. It then takes that output and stores it in a format most efficient
for OpenGL rendering.

Rendering modes supported are
- Bit maps
- Antialiased Pix maps
- Texture maps
- Outlines
- Polygon meshes
- Extruded polygon meshes

FTGL is designed to be used in commercial quality software. It has been
written with performance, robustness and simplicity in mind.

USAGE:

	FTGLPixmapFont font;
	
	font.Open( "Fonts:Arial");
	font.FaceSize( 72);
	
	font.render( "Hello World!");

This library was inspired by gltt, Copyright (C) 1998-1999 Stephane Rehel
(http://gltt.sourceforge.net)
Bezier curve code contributed by Jed Soane.
Demo, Linux port, extrusion code and gltt maintainance by Gerard Lanois
Linux port by Matthias Kretz
Windows port by Max Rheiner
Bug fixes by Robert Osfield

Please contact me if you have any suggestions, feature requests, or problems.

Henry Maddocks
henryj@paradise.net.nz
http://homepages.paradise.net.nz/henryj/



//========================================================================

Things to think about...

The whole char size thing is major headache.
At the moment if you call font.CharSize( x) the glyph list is destroyed and
rebuilt, which will be really, really, really inefficient if you change sizes
often. Will the freetype cache stuff help? What about the new (FT 2.0.5)
FTSize public api.

When is the best time to construct the glyphList? After the call to Size(x)
is the earliest but what happens if the client doesn't set the char size?
Define a default size, check if glyphlist is valid in render function, if
not call size with default size.

Might have to move the init code out of the glyph constructors into an
init function so that they can return errors.

good sites...
http://cgm.cs.mcgill.ca/~luc/
http://www.blackpawn.com/texts/lightmaps/default.html

glGetIntegerv( GL_TEXTURE_2D_BINDING_EXT, &activeTextureID);
should really check at run time.



Check that I do this properly..
============================

Dave Williss a Žcrit :

Question:

If I do this...

    TT_New_Glyph(face, &glyph);
    for (i = 0 ; i < n ; ++i) {
        TT_Load_Glyph(instance, glyph, index[i], flags);
            ... use glyph...
    }

    TT_Done_Glyph(glyph)

Will I be leaking memory on each call to Load Glyph or
should I create and destroy the glyph handle for each call?
Seems terribily inefficient but to do that, but doing it as
above I seem to be leaking memory.


No, this is the correct behaviour. Each call to TT_Load_Glyph
overwrites the previous content.. and this was designed on
purpose because the real content of a TT_Glyph object is
_really_ complex with TrueType, and you don't want to create
them on each glyph load..
