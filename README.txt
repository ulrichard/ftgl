FTGL 1.0b5
August 29 2001

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

Please contact me if you have any suggestions, feature requests, or problems.

Henry Maddocks
henryj@paradise.net.nz
http://homepages.paradise.net.nz/henryj/


Things to think about...
The whole char size thing is major headache.
At the moment if you call font.CharSize( x) the glyph list is destroyed and
rebuilt, which will be really, really, really inefficient if you change sizes
often. Will the freetype cache stuff help here or should we cache internally?
Multiple glyphlists. glyphlist manager. Multiple glyphLists will chew up
memory. Maybe a <map> will help here, maybe a map will let us cache glyphs
as required rather than all at startup? This wont help texture glyphs.
If we allow multiple faces and sizes how should they be handled.

When is the best time to construct the glyphList? After the call to Size(x)
is the earliest but what happens if the client doesn't set the char size?
Define a default size, check if glyphlist is valid in render function, if
not call size with default size.
 
Need a way to restrict the glyphs to a custom set. eg an app only needs
numbers so we should only create a glyphList of the number characters.
This will enable us to have a restricted set of HIGH quality glyphs.

Might have to move the init code out of the glyph constructors into an
init function so that they can return errors.

Currently the glyphList is isn't indexed, it's just a vector of glyphs in
glyphIndex order. I'm using the freetype function FT_Get_Char_Index() to
convert char codes to glyphIndices. If this proves to be too slow I will
implement a charmap class that will hold the indices.

good site...http://cgm.cs.mcgill.ca/~luc/

Apparently...C++ guarantees that delete can safely be called on a NULL
pointer. Something to remember for the future.

PROFILING
test 1
100,000 frames. No openGL context.
The results of the first profile are in and as expected using freetype to
return the char index for a glyph is costing us. A staggering 10% of the
rendering time in fact!!! Kerning has a similar impact.

TODO:
	- Tidy code, fix compiler warnings, comments.
	- Memory Leak in PolyGlyph (glCombine)
	- check and confirm the glPixelStore stuff. Data Alignment. Tightly
	  packed at the moment.
	- namespace ftgl or gltt?
	- gl/glu errors
	- tessellation winding rules
	- Distributions MACOS 9/X, IRIX, Linux, Windows
	- Test with non European (Roman?) fonts
	
FUTURE:
	- select face ie italic, bold etc
	- Multiple sizes
	- Optimise performance!! and mem usage.
	  - don't process chars that map to glyph 0
	  - Make our own char map processing class
	- GL evaluators. Are they of any use?
	- Use the Freetype Cache mechanism. See above. FTC_xxx
	- Alignment. left right, centre.
	- Bounding box, char and string.
	- Vertical formats
	- For platforms that have antialiased lines but not polys we could
	  outline the polyfonts with lines to get better looking glyphs.
	- Unicode w_char. May have to use std::wstring and or std::wchar_t.
	- Improve the grid fitting scheme in texture fonts.
	- Helper classes...
	  - String Cache
	  - Provide an interface to access the point data for outlines and
	    polygon meshes.


BUGS:
	- Advance/Kerning is screwed up for really small point sizes eg 2 point.
	  This is because I'm trying to use FT_Vector which is integer based.
	  I will probably have to make my own struct with floats.
	- The texture co-ords in the Texture Font may be wrong for non
	  scalable fonts.
	- There is an inconsistancy in the way the global bounding box is
	  stored in Freetype. It is supposed to be in font units but in some
	  cases it is in 16.16 format. I have implemented a work around but
	  hopefully the freetype guys will sort this.
	MAC OS:
		- Exits with some fonts at large sizes. GLUT Memory Bug?
		  also with large numbers of glyphs at any size eg helvetica. This
		  is becoming REALLY annoying!!!


	1.0b6
	- Tidied up the way the freetype FT_Face object is disposed of by
	  FTFont and FTFace. This was a potential crash.
	- FTVectorGlyph and FTPolyGlyph now disposed of the freetype glyph
	  correctly after initialsation. This was a potential crash.
	-


August 29 2001
	1.0b5
	- Settled on integers for FTSize stuff. NOTE the FTGlyph stuff is still
	  up in the air.
	- Fixed the positional stuff.
	- Added Java Doc comments. NOT COMPLETE
	- Fixes for linux, mainly to clear warnings.
	- changed the return type for FTFace::Glyph() from a reference to a
	  pointer so it can return NULL on failure.
	- Related to above...better error handling and reporting in
	  FTGLXXXFont::MakeGlyphList()
	- Fixed a bug in FTVectoriser that was ignoring non printing characters.
	  This meant that the pen wasn't advanced for spaces etc. It affected
	  polygon and outline font rendering.
	- Minor tidy ups.
	
	
August 21 2001
	1.0b4
	- Changed the mode for FT_Load_Glyph to FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP
	  for outline and polygon fonts & FT_LOAD_NO_HINTING for texture fonts.
	  Seems to produce better looking glyphs.
	- FTGLTextureFont can now use multiple textures to render glyphs if
	  they don't fit within one GL_MAX_TEXTURE_SIZE texture. 
	- Changed FTSize to use bbox for global width and height. Needs more
	  work (eg float or int?) and need to check inconsistancies in freetype.
	- Being more strict with types eg integer indices and sizes are now unsigned.


August 8 2001
	1.0b3
	- I've made fundamental change to the way the glyphlist is built. This
	  is to get round the problems I was having with charmaps. At this stage
	  it is a temporary solution. Previously the glyphList was indexed by
	  char code. Now it's indexed by glyph index and the conversion is done
	  by the freetype function FT_Get_Char_Index(). If this proves to be too
	  slow I'll make my own charmap and use it to index into the glyphlist.
	  This has fixed all the charmap related problems/bugs.
	- Enabled alpha blend in Pixmap font.
	- Enabled LINE_SMOOTH in Outline font
	- Fixed bug that prevented the display of chars >127
	- Moved pixel store stuff out of BitmapGlyph into BitmapFont.
	- Minor changes for IRIX (compiles but isn't tested)
	- Pixmap fonts can now be in colour. It uses the current colour when the
	  font is CREATED. This isn't ideal but is better then the alternatives.
	- Tidied up the error handling.
	- Minor code clean ups.


August 6 2001
	BETA release 1.0b2
	- Minor tidy ups for first public release.
	
August 3 2001
	First BETA release 1.0b1
	- All font types are now working, Bitmaps, Pixmaps, Texture, Outline
	  and Polygons. Quality of output and performance varies wildly:)

July 22 2001
	First ALPHA Release 1.0a1

