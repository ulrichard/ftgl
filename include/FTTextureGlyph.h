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
		FTTextureGlyph( FT_Glyph glyph, int gi, unsigned char* data, int stride, float u, float v);
		virtual ~FTTextureGlyph();
		virtual float Render( const FT_Vector& v);
		
	private:
		// attributes
		// What about the other point class in vectoriser?
		struct FTPoint
		{
			float x;
			float y;
		};

		int destWidth;
		int destHeight;
		
		int numGreys;
		
		FTPoint uv[2];
};


#endif	//	__FTTextureGlyph__
