#ifndef		__FTGLBitmapFont
#define		__FTGLBitmapFont


#include	"FTFont.h"

class FTBitmapGlyph;

class	FTGLBitmapFont : public FTFont
{
	public:
		// methods
		FTGLBitmapFont();
		~FTGLBitmapFont();
		
		// attributes
		
	private:
		// methods
		bool MakeGlyphList();
		
		// attributes
		FTBitmapGlyph* tempGlyph;
		
};
#endif
