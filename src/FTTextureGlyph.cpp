#include	"gl.h"

#include	"FTTextureGlyph.h"
#include	"FTGL.h"


FTTextureGlyph::FTTextureGlyph( FT_Glyph glyph, int gi, unsigned char* data, int stride, float u, float v)
:	FTGlyph(gi),
	destWidth(0),
	destHeight(0),
	numGreys(0)
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
	pos.y = bitmap->top;
	
    destWidth = srcWidth;
    destHeight = srcHeight;
    
    for(int y = 0; y < srcHeight; ++y)
    {
    	for(int x = 0; x < srcWidth; ++x)
    	{
			*( data + ( y * stride  + x)) = *( source->buffer + ( y * srcPitch) + x);
    	}    	
    }

//		0    
//		+----+
//		|    |
//		|    |
//		|    |
//		+----+
//		     1
	
	uv[0].x = u;
	uv[0].y = v;
	uv[1].x = uv[0].x + ( (float)destWidth / (float)stride);
	uv[1].y = uv[0].y + ( (float)destHeight / (float)stride);

	// discard glyph image (bitmap or not)
	// Is this the right place to do this?
	FT_Done_Glyph( glyph );
}


FTTextureGlyph::~FTTextureGlyph()
{

}


float FTTextureGlyph::Render( const FT_Vector& pen)
{
//	int adv = advance/* + pos.x */+ ( v.x >> 16); // FIXME ??? pos.x = bearing X

	glTexCoord2f( uv[0].x, uv[0].y); glVertex2f( pen.x,				pen.y + pos.y);
	glTexCoord2f( uv[1].x, uv[0].y); glVertex2f( pen.x + destWidth,	pen.y + pos.y);
	glTexCoord2f( uv[1].x, uv[1].y); glVertex2f( pen.x + destWidth,	pen.y + pos.y - destHeight);
	glTexCoord2f( uv[0].x, uv[1].y); glVertex2f( pen.x,				pen.y + pos.y - destHeight);

	return advance;
}
