#include	"gl.h"

#include	"FTTextureGlyph.h"
#include	"FTGL.h"


FTTextureGlyph::FTTextureGlyph( FT_Glyph glyph, int gi, pointer to data location, stride)
:	FTGlyph(gi)
{
	if( !glyph->format == ft_glyph_format_bitmap)
	{ return;}
	
	// This function will always fail if the glyph's format isn't scalable????
	err = FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1);
	if( err)
	{return;}

	FT_BitmapGlyph  bitmap = (FT_BitmapGlyph)glyph;
	FT_Bitmap*      source = &bitmap->bitmap;

	//check the pixel mode
	//ft_pixel_mode_grays
	    
	int srcWidth = source->width;
	int srcHeight = source->rows;
	int srcPitch = source->pitch;
    
	numGreys = source->num_grays;
	advance = glyph->advance.x >> 16; // this is 6 in the freetype docs!!!!!!

 	pos.x = bitmap->left;
	pos.y = srcHeight - bitmap->top;
	
   // FIXME The buffer is upside down. What about dest alignment?
    destWidth = srcWidth;
    destHeight = srcHeight;
    
    data = new unsigned char[destWidth * destHeight * 4];
    
    for(int y = 0; y < srcHeight; ++y)
    {
    	--destHeight;
    	for(int x = 0; x < srcWidth; ++x)
    	{
			*( data + ( destHeight * destWidth  + x) * 4 + 0) = 0xFF;
			*( data + ( destHeight * destWidth  + x) * 4 + 1) = 0xFF;
			*( data + ( destHeight * destWidth  + x) * 4 + 2) = 0xFF;
			*( data + ( destHeight * destWidth  + x) * 4 + 3) = *( source->buffer + ( y * srcPitch) + x);
    	}    	
    }

    destHeight = srcHeight;

	// discard glyph image (bitmap or not)
	// Is this the right place to do this?
	FT_Done_Glyph( glyph );
}


FTTextureGlyph::~FTTextureGlyph()
{
	delete[] data;
}


float FTTextureGlyph::Render( FT_Vector v)
{
	int adv = advance/* + pos.x */+ ( v.x >> 16); // FIXME ??? pos.x = bearing X
	if( data != 0 )
	{
		// Move the glyph origin
		glBitmap( 0, 0, 0.0, 0.0, 0, -pos.y, (const GLubyte *)0 );

		glPixelStorei( GL_UNPACK_ROW_LENGTH, destWidth);

		glDrawPixels( destWidth, destHeight, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)data );

		// Restore the glyph origin
		glBitmap( 0, 0, 0.0, 0.0, 0, pos.y, (const GLubyte *)0 );
	}
	
	// Advance the raster pos.
	glBitmap( 0, 0, 0.0, 0.0, adv, 0, (const GLubyte *)0 );

	return advance;
}