FTGL 1.0b1

DESCRIPTION:
FTGL is a library a tool to allow OpenGL (www.opengl.org) to render
characters from arbitary fonts.
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



Things to think about...
The whole char size thing is major headache
At the moment if you call font.CharSize( x) the glyph list is destroyed and
rebuilt, which will be really, really, really inefficient if you change sizes
often. Will the freetype cache stuff help here or should we cache internally?
Multiple glyphlists. glyphlist manager. FTSize obj???
Multiple glyphLists will chew up memory. Maybe a <map> will help here, maybe
a map will let us cache glyphs as required rather than all at startup? This
wont help texture glyphs.

The FTSize seems redundant. (depends on the out come of the above)

If a font is defined uniquely by it's face and size ie
font.Open("Fonts:Arial", 72);
Then we don't need FTFace and FTSize, their functionality could be internal
to FTFont. Alternatively if we allow multiple faces and sizes how should
they be handled.

When is the best time to construct the glyphList? After the call to Size(x)
is the earliest but what happens if the client doesn't set the char size?

Need a way to restrict the glyphs to a custom set. eg an app only needs
numbers so we should only create a glyphList of the number characters.
This will enable us to have a restricted set of HIGH quality glyphs.

Might have to move the init code out of the constructers into an init
function so that they can return errors.


TODO:
	- Finish!!
	- Error handling - fail gracefully - return FT_Error codes.
	- The position stuff is broken again. Check the pen stuff. Plus lower
	  case 'y's seem to be 1 pixel too low?
	- Use glRasterPos() not glBitMap to set raster pos in pixel fonts.
	- check and confirm the glPixelStore stuff. Data Alignment. Tightly
	  packed at the moment.
	- Clear the texture mem
	- calc smallest texture size
	- overflow texture
	- Coloured Pixmaps
	- Optimise performance!! and mem usage.
	  - don't process chars that map to glyph 0
	  - variable STEP_SIZE for bezier curves.
	- namespace
	- gl/glu errors
	- tesselation winding rules
	- Distributions MACOS 9/X, IRIX, Linux, Windows
	- Test with non English(?) fonts
	- select face ie italic, bold etc
	
FUTURE:
	- Use the Freetype Cache mechanism. See above. FTC_xxx
	- Alignment. left right, centre.
	- Bounding box, char and string.
	- Vertical formats
	- For platforms that have antialiased lines but not polys (sgi O2) we
	  could outline the polyfonts with lines to get better looking glyphs.
	- Provide an interface to acces the point data for outlines and polygon
	  meshes.

BUGS:
	MAC OS:
		- Exits with some fonts at large sizes. Freetype or GLUT Memory Bug?
		  also with large numbers of glyphs at any size eg helvetica


August 3 2001
	- First BETA release 1.0b1
	- All font types are now working, Bitmaps, Pixmaps, Texture, Outline
	  and Polygons. Quality of output and performance varies wildly:)

July 22 2001
	- First ALPHA Release 1.0a1


