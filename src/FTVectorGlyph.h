#ifndef		__FTVectorGlyph__
#define		__FTVectorGlyph__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTGlyph.h"


class	FTVectorGlyph : public FTGlyph
{
	public:
		// methods
		FTVectorGlyph( FT_Glyph glyph, int glyphIndex);
		virtual ~FTVectorGlyph();
		virtual float Render();
		
		// attributes
		
};


#endif	//	__FTVectorGlyph__
