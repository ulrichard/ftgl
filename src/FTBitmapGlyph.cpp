#include "FTBitmapGlyph.h"

FTBitmapGlyph::FTBitmapGlyph( FT_Glyph glyph)
:   FTGlyph(),
    destWidth(0),
    destHeight(0),
    data(0)
{
    // This function will always fail if the glyph's format isn't scalable????
    err = FT_Glyph_To_Bitmap( &glyph, ft_render_mode_mono, 0, 1);
    if( err || ft_glyph_format_bitmap != glyph->format)
    {
        return;
    }

    FT_BitmapGlyph  bitmap = (FT_BitmapGlyph)glyph;
    FT_Bitmap*      source = &bitmap->bitmap;

    //check the pixel mode
    //ft_pixel_mode_grays
        
    unsigned int srcWidth = source->width;
    unsigned int srcHeight = source->rows;
    unsigned int srcPitch = source->pitch;
    
   // FIXME What about dest alignment?
    destWidth = srcWidth;
    destHeight = srcHeight;
    
    if( destWidth && destHeight)
    {
        data = new unsigned char[srcPitch * destHeight];
        unsigned char* dest = data + (( destHeight - 1) * srcPitch);

        unsigned char* src = source->buffer;
        size_t destStep = srcPitch * 2;
        
        for( unsigned int y = 0; y < srcHeight; ++y)
        {
            for( unsigned int x = 0; x < srcPitch; ++x)
            {
                *dest++ = *src++;
            }
            
            dest -= destStep;
        }
    }
    
    bBox = FTBBox( glyph);
    advance = static_cast<float>(glyph->advance.x >> 16);
    pos.x = bitmap->left;
    pos.y = static_cast<int>(srcHeight) - bitmap->top;
    
    // Is this the right place to do this?
    FT_Done_Glyph( glyph );
}


FTBitmapGlyph::~FTBitmapGlyph()
{
    delete [] data;
}


float FTBitmapGlyph::Render( const FTPoint& pen)
{
    if( data)
    {
        // Move the glyph origin
        glBitmap( 0, 0, 0.0, 0.0, pen.x + pos.x, pen.y - pos.y, (const GLubyte*)0 );

        glBitmap( destWidth, destHeight, 0.0f, 0.0, 0.0, 0.0, (const GLubyte*)data);

        // Restore the glyph origin
        glBitmap( 0, 0, 0.0, 0.0, -pen.x - pos.x, -pen.y + pos.y, (const GLubyte*)0 );
    }
    
    return advance;
}
