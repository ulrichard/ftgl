#ifndef		__FTGlyph__
#define		__FTGlyph__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

//#include "FTGL.h"


class FTGlyph
{
	public:
		// methods
		FTGlyph( int glyphIndex);
		virtual ~FTGlyph();
		virtual float Render( FT_Vector& v) = 0;
		
		FT_Error Error() const { return err;}
		
		// attributes
		const int glyphIndex;
		
	protected:
		// methods
		
		// attributes
		FT_Error err;
		
		float advance;
		FT_Vector pos;
		FT_Glyph ftGlyph;
		
	private:
		// methods
		
		// attributes
		
};


#endif	//	__FTGlyph__
