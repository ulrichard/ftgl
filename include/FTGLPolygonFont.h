#ifndef		__FTGLPolygonFont__
#define		__FTGLPolygonFont__

#include	"FTFont.h"

#include "FTGL.h"


class FTPolyGlyph;

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
		
		// attributes
		FTPolyGlyph* tempGlyph;

		
};
#endif	//	__FTGLPolygonFont__
