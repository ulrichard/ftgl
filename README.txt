FTGL 1.0a1


USAGE:

	FTGLPixmapFont font;
	
	font.Open("HenrysHD:System Folder:Fonts:Arial");
	font.FaceSize( 72);
	
	font.render("Hello World!");



Things to think about...
If a font is defined uniquely by it's face and size ie
font.Open("HenrysHD:System Folder:Fonts:Arial", 72);
Then we don't need FTFace and FTSize, their functionality could be internal
to FTFont. Alternatively if we allow multiple faces and sizes how should
they be handled.
At the moment if you call font.CharSize( x) the glyph list is destroyed and
rebuilt, which will be really inefficient if you change sizes often. Will
the freetype cache stuff help here or should we cache internally?
multiple glyphlists. glyphlist manager.

When is the best time to construct the glyphList? After the call to Size(x)
is the earliest but what happens if the client doesn't set the char size?

The FTSize seems redundant.

TODO:
	- Finish!!
	- Error handling - fail gracefully - return FT_Error codes.
	- What happens with 2 obj of the same font type
	- Kerning. The position stuff now seems OK but needs checking. (lower
	  case 'y's seem to be 1 pixel too low?)
	- check and confirm the glPixelStore stuff. Data Alignment. Tightly
	  packed at the moment.
	- FTOutlineGlyph
	- FTPolygonGlyph
	- Change glDrawPixels to use GL_ALPHA instead of GL_RGBA. This may not
	  work, read red book.
	- Coloured Pixmaps/ bitmaps
	- Optimise performance!! and mem usage.
	- Use the Freetype Cache mechanism. See above. FTC_xxx
	- Sort out the pixel storage modes.
	- Pixmaps as textures. FTTextureGlyph
	- Vertical formats
	
	
BUGS:
	MAC OS:
		- Exits with some fonts at large sizes. Memory?
		


July 22 2001
	- First ALPHA Release 1.0a1


