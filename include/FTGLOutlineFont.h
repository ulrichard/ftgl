#ifndef		__FTGLOutlineFont
#define		__FTGLOutlineFont


#include	"FTFont.h"
#include "FTGL.h"


class FTVectorGlyph;

class	FTGLOutlineFont : public FTFont
{
	public:
		// methods
		FTGLOutlineFont();
		~FTGLOutlineFont();
		
		void render( const char* string);

		// attributes
		
	private:
		// methods
		bool MakeGlyphList();
		
		// attributes
		FTVectorGlyph* tempGlyph;
	
};
#endif
