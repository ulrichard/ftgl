#ifndef		__FTGLPixmapFont__
#define		__FTGLPixmapFont__


#include	"FTFont.h"

class FTPixmapGlyph;

class	FTGLPixmapFont : public FTFont
{
	public:
		// methods
		FTGLPixmapFont();
		~FTGLPixmapFont();
		
		void render( const char* string);


	private:
		// methods
		bool MakeGlyphList();
		
		// attributes
		FTPixmapGlyph* tempGlyph;
		
};


#endif	//	__FTGLPixmapFont__
