#ifndef		__FTFace__
#define		__FTFace__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTSize.h"

#include "FTGL.h"


class	FTFace
{
	public:
		// methods
		FTFace();
		virtual ~FTFace();
		bool Open( const char* filename);
		void Close();
		FTSize& Size( const int size, const int res );
		bool CharMap( CHARMAP encoding );
		FT_Glyph Glyph( int index );
		FT_Vector KernAdvance( int index1, int index2 );
		FT_Face* Face() const { return ftFace;}
		
		// attributes
		
	private:
		// methods
		
		// attributes
//		FONTTYPE	fontType;
		FTSize	charSize;
		FT_Face* ftFace;
		int	numCharMaps;
		int	numGlyphs;
		
};


#endif	//	__FTFace__
