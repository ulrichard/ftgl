#ifndef		__FTGLBitmapFont__
#define		__FTGLBitmapFont__


#include	"FTFont.h"

class FTBitmapGlyph;

class	FTGLBitmapFont : public FTFont
{
	public:
		// methods
		FTGLBitmapFont();
		~FTGLBitmapFont();
		
		void render( const char* string);

		// attributes
		
	private:
		// methods
		bool MakeGlyphList();
		
		// attributes
		FTBitmapGlyph* tempGlyph;
		
};
#endif	//	__FTGLBitmapFont__
