FTGL 1.0b3
August 8 2001

DESCRIPTION:
FTGL is a library a tool to allow OpenGL (www.opengl.org) to render
characters from arbitrary fonts.
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


USAGE:

	FTGLPixmapFont font;
	
	font.Open( "Fonts:Arial");
	font.FaceSize( 72);
	
	font.render( "Hello World!");


This library was inspired by gltt, Copyright (C) 1998-1999 Stephane Rehel
( gltt.sourceforge.net)



Things to think about...
The whole char size thing is major headache.
At the moment if you call font.CharSize( x) the glyph list is destroyed and
rebuilt, which will be really, really, really inefficient if you change sizes
often. Will the freetype cache stuff help here or should we cache internally?
Multiple glyphlists. glyphlist manager. Multiple glyphLists will chew up
memory. Maybe a <map> will help here, maybe a map will let us cache glyphs
as required rather than all at startup? This wont help texture glyphs.
If a font is defined uniquely by it's face and size ie
font.Open("Fonts:Arial", 72);
Then we don't need FTFace and FTSize, their functionality could be internal
to FTFont. Alternatively if we allow multiple faces and sizes how should
they be handled. The FTSize seems redundant (depends on the out come of the
above). For the time being I'm treating this as a feature!

When is the best time to construct the glyphList? After the call to Size(x)
is the earliest but what happens if the client doesn't set the char size?

Need a way to restrict the glyphs to a custom set. eg an app only needs
numbers so we should only create a glyphList of the number characters.
This will enable us to have a restricted set of HIGH quality glyphs.

Might have to move the init code out of the constructors into an init
function so that they can return errors.

Currently the glyphList is isn't indexed, it's just a vector of glyphs in
glyphIndex order. I'm using the freetype function FT_Get_Char_Index() to
convert char codes to glyphIndices. If this proves to be too slow I will
implement a charmap class that will hold the indices.

good site...http://cgm.cs.mcgill.ca/~luc/


TODO:
	- Finish!!
	- Fix compiler warnings
	- The position stuff is broken again. Check the pen stuff. Plus lower
	  case 'y's seem to be 1 pixel too low?
	- Use glRasterPos() not glBitMap to set raster pos in pixel fonts.
	- check and confirm the glPixelStore stuff. Data Alignment. Tightly
	  packed at the moment.
	- Clear the texture mem
	- calc smallest texture size
	- overflow texture
	- namespace
	- gl/glu errors
	- tessellation winding rules
	- Distributions MACOS 9/X, IRIX, Linux, Windows
	- Test with non English(?) fonts
	- Unicode w_char. May have to use std::wstring and or std::wchar_t.
	
FUTURE:
	- select face ie italic, bold etc
	- select charmap
	- Multiple sizes
	- Optimise performance!! and mem usage.
	  - don't process chars that map to glyph 0
	  - variable STEP_SIZE for bezier curves.
	- Use the Freetype Cache mechanism. See above. FTC_xxx
	- Alignment. left right, centre.
	- Bounding box, char and string.
	- Vertical formats
	- For platforms that have antialiased lines but not polys we could
	  outline the polyfonts with lines to get better looking glyphs.
	- Provide an interface to access the point data for outlines and polygon
	  meshes.

BUGS:
	MAC OS:
		- Exits with some fonts at large sizes. GLUT Memory Bug?
		  also with large numbers of glyphs at any size eg helvetica. This
		  is becoming REALLY annoying!!!


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


