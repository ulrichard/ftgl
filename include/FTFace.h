#ifndef		__FTFace__
#define		__FTFace__

//#include "FTGL.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTSize.h"



class	FTFace
{
	public:
		// methods
		FTFace();
		virtual ~FTFace();
		bool Open( const char* filename);
		void Close();
		
		FTSize& Size( const unsigned int size, const unsigned int res);
		bool CharMap( FT_Encoding encoding);
		unsigned int CharIndex( unsigned int index ) const;
		FT_Vector& KernAdvance( unsigned int index1, unsigned int index2);
		
		FT_Glyph& Glyph( unsigned int index, FT_Int load_flags);
		FT_Face* Face() const { return ftFace;}
		
		FT_Error Error() const { return err;}
		
		// attributes
		
	private:
		// methods
		
		// attributes
		FT_Error err;
		FTSize	charSize;
		FT_Face* ftFace;
		FT_Glyph ftGlyph;
		
		int	numCharMaps;
		int	numGlyphs;
		
		FT_Vector kernAdvance;
		
};


#endif	//	__FTFace__
