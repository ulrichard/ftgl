#ifndef		__FTPolyGlyph__
#define		__FTPolyGlyph__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTGlyph.h"

class FTVectoriser;

class	FTPolyGlyph : public FTGlyph
{
	public:
		// methods
		FTPolyGlyph( FT_Glyph glyph, int glyphIndex);
		virtual ~FTPolyGlyph();
		virtual float Render( FT_Vector& pen);
		
		// attributes
	
	private:
		// methods
		void Tesselate();
		
		// attributes
		FTVectoriser* vectoriser;
		int numPoints;
		int numContours;
		int * contourLength;
		float* data;
		int glList;
	
};


#endif	//	__FTPolyGlyph__
