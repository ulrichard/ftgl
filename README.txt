FTGL 1.0b1


USAGE:

	FTGLPixmapFont font;
	
	font.Open( "HenrysHD:System Folder:Fonts:Arial");
	font.FaceSize( 72);
	
	font.render( "Hello World!");



Things to think about...
If a font is defined uniquely by it's face and size ie
font.Open("Fonts:Arial", 72);
Then we don't need FTFace and FTSize, their functionality could be internal
to FTFont. Alternatively if we allow multiple faces and sizes how should
they be handled.
At the moment if you call font.CharSize( x) the glyph list is destroyed and
rebuilt, which will be really inefficient if you change sizes often. Will
the freetype cache stuff help here or should we cache internally?
multiple glyphlists. glyphlist manager. FTSize obj???

When is the best time to construct the glyphList? After the call to Size(x)
is the earliest but what happens if the client doesn't set the char size?

The FTSize seems redundant. (depends on the out come of the above)

Need a way to restrict the glyphs to a custom set. eg an app only needs
numbers so we should only create a glyphList of the number characters.
This will enable us to have a restricted set of HIGH quality glyphs.

TODO:
	- Finish!!
	- Error handling - fail gracefully - return FT_Error codes.
	- What happens with 2 obj of the same font type
	- The position stuff is broken again. Check the pen stuff. Plus lower
	  case 'y's seem to be 1 pixel too low?)
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
	
FUTURE:
	- pen position eg font.render( 50, 100, "Hello World!");
	- Use the Freetype Cache mechanism. See above. FTC_xxx
	- Alignment. left right, centre.
	- Bounding box, char and string.
	- Vertical formats

BUGS:
	MAC OS:
		- Exits with some fonts at large sizes. Freetype or GLUT Memory Bug?


August 3 2001
	- First BETA release 1.0b1
	- All font types are now working, Bitmaps, Pixmaps, Texture, Outline
	  and Polygons. Quality of output and performance varies wildly:)

July 22 2001
	- First ALPHA Release 1.0a1


