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

TODO:
	- Tidy code, fix compiler warnings, comments.
	- namespace ftgl or gltt?
	- Distributions MACOS 9/X, IRIX, Linux, Windows
	
FUTURE:
	- Memory Leak in PolyGlyph (glCombine). This may disappear when access
	  to the point data is sorted.
	- select face ie italic, bold etc
	- Multiple sizes
	- Optimise performance and mem usage.
	- GL evaluators. Are they of any use?
	- gl/glu errors
	- tessellation winding rules
	- check and confirm the glPixelStore stuff. Data Alignment. Tightly
	  packed at the moment.
	- Use the Freetype Cache mechanism. See above. FTC_xxx
	- Vertical formats
	- For platforms that have antialiased lines but not polys we could
	  outline the polyfonts with lines to get better looking glyphs.
	- Improve the grid fitting scheme in texture fonts.
	- Multiple Masters
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


September 20 2001
	1.0b6
	- Implemented the new FTCharmap class. The performance improvement
	  is dramatic.
	- Tidied up the way the freetype FT_Face object is disposed of by
	  FTFont and FTFace. This was a potential crash.
	- FTVectorGlyph and FTPolyGlyph now disposes of the freetype glyph
	  correctly after initialsation. This was a potential crash.
	- Preliminary support for unicode...wchar_t Tested with non european
	  fonts.
	- Added function to calc the advance width of a string.
	- Minor tidy ups.


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

