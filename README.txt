FTGL 1.0b6
September 20 2001

DESCRIPTION:
FTGL library is a cross platform tool to allow OpenGL (www.opengl.org) to
render characters from arbitrary fonts.
Unlike other OpenGL font libraries FTGL uses standard font file formats
so doesn't need a preprocessing step to convert the high quality font data
into a lesser quality, proprietary format.
FTGL uses the Freetype (www.freetype.org) font library to open and 'decode'
the fonts. It then takes that output and stores it in a format most efficient
for OpenGL rendering.

Rendering modes supported are
- Bit maps
- Pix maps
- Texture maps
- Outlines
- Polygon meshes

FTGL is designed to be used in commercial quality software. It has been
written with performance, robustness and simplicity in mind.

USAGE:

	FTGLPixmapFont font;
	
	font.Open( "Fonts:Arial");
	font.FaceSize( 72);
	
	font.render( "Hello World!");

This library was inspired by gltt, Copyright (C) 1998-1999 Stephane Rehel
( gltt.sourceforge.net)
Bezier curve code contributed by Jed Soane.
Demo, Linux port and gltt maintainance by Gerard Lanois
Linux port by Matthias Kretz
Windows port by Max Rheiner

Please contact me if you have any suggestions, feature requests, or problems.

Henry Maddocks
henryj@paradise.net.nz
http://homepages.paradise.net.nz/henryj/


Things to think about...
The whole char size thing is major headache.
At the moment if you call font.CharSize( x) the glyph list is destroyed and
rebuilt, which will be really, really, really inefficient if you change sizes
often. Will the freetype cache stuff help?

When is the best time to construct the glyphList? After the call to Size(x)
is the earliest but what happens if the client doesn't set the char size?
Define a default size, check if glyphlist is valid in render function, if
not call size with default size.
 
Need a way to restrict the glyphs to a custom set. eg an app only needs
numbers so we should only create a glyphList of the number characters.
This will enable us to have a restricted set of HIGH quality glyphs.

Might have to move the init code out of the glyph constructors into an
init function so that they can return errors.

good site...http://cgm.cs.mcgill.ca/~luc/

PROFILING
test 1
100,000 frames. No openGL context.
The results of the first profile are in and as expected using freetype to
return the char index for a glyph is costing us. A staggering 10% of the
rendering time in fact!!! Kerning has a similar impact.

test 2
100,000 frames. No openGL context.
Performance results for the new FTCharmap class are quite satisfying:)
The overall render time went from 12.009 seconds down to 4.595. The
charIndex call went from 9.066 to 1.754. My concerns about the performance
of std::map seemed to be unfounded in this case. Kerning is still an issue
as can be seen in the proportional difference in these figures. I don't think
this can be resolved easily.

