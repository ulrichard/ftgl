FTGL 1.4
October 23 2002


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

	FTGLPixmapFont font( "Fonts:Arial");

	font.FaceSize( 72);
	
	font.render( "Hello World!");

This library was inspired by gltt, Copyright (C) 1998-1999 Stephane Rehel
(http://gltt.sourceforge.net)
Bezier curve code contributed by Jed Soane.
Demo, Linux port, extrusion code and gltt maintainance by Gerard Lanois
Linux port by Matthias Kretz
Windows port by Max Rheiner & Andrew Ellerton
Bug fixes by Robert Osfield, Marcelo E. Magallon, Markku Rontu, Mark A. Fox
Containers and optimisations by Sebastien Barre

Please contact me if you have any suggestions, feature requests, or problems.

Henry Maddocks
henryj@paradise.net.nz
http://homepages.paradise.net.nz/henryj/

