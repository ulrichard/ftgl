#ifndef		__FTPixmapGlyph__
#define		__FTPixmapGlyph__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include	"FTGlyph.h"


class FTPixmapGlyph : public FTGlyph
{
	public:
		// methods
		FTPixmapGlyph( FT_Glyph glyph, const int glyphIndex);
		virtual ~FTPixmapGlyph();
		virtual float Render( const FT_Vector& v);
		
		// attributes

	private:
		// methods
		
		// attributes
		int destWidth;
		int destHeight;
		
		int numGreys;

		unsigned char* data;
		
};


#endif	//	__FTPixmapGlyph__
