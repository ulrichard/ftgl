#ifndef		__FTGLPolygonFont
#define		__FTGLPolygonFont
#include	"FTFont.h"

#include "FTGL.h"

class	FTGLPolygonFont : public FTFont
{
	public:
		// methods
		FTGLPolygonFont();
		~FTGLPolygonFont();
		
		// attributes
		
	private:
		// methods
		bool MakeGlyphList();
		
};
#endif
