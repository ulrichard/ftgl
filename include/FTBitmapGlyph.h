#ifndef		__FTBitmapGlyph__
#define		__FTBitmapGlyph__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include	"FTGlyph.h"


class	FTBitmapGlyph : public FTGlyph
{
	public:
		// methods
		FTBitmapGlyph( FT_Glyph glyph, int glyphIndex);
		virtual ~FTBitmapGlyph();
		virtual float Render( FT_Vector v);
		
		// attributes
		
	private:
		// methods
		
		// attributes
		int destWidth;
		int destHeight;
		
		unsigned char* data;
		
};


#endif	//	__FTBitmapGlyph__
