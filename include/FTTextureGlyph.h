#ifndef		__FTTextureGlyph__
#define		__FTTextureGlyph__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include	"FTGlyph.h"


class	FTTextureGlyph : public FTGlyph
{
	public:
		// methods
		FTTextureGlyph( FT_Glyph glyph, int glyphIndex);
		virtual ~FTTextureGlyph();
		virtual float Render( FT_Vector v);
		
		// attributes
		int destWidth;
		int destHeight;
		
		int numGreys;

		unsigned char* data;
		
		FT_Vector uv[4];
};


#endif	//	__FTTextureGlyph__
