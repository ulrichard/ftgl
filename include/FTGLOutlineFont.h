#ifndef		__FTGLOutlineFont
#define		__FTGLOutlineFont
#include	"FTFont.h"

#include "FTGL.h"

class	FTGLOutlineFont : public FTFont
{
	public:
		// methods
		FTGLOutlineFont();
		~FTGLOutlineFont();
		
		// attributes
		
	private:
		// methods
		bool MakeGlyphList();
		
};
#endif
