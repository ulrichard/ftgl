#include	"FTGLPolygonFont.h"
#include	"FTGlyphContainer.h"
#include	"FTGL.h"
#include	"FTPolyGlyph.h"



FTGLPolygonFont::FTGLPolygonFont()
:	tempGlyph(0)
{}


FTGLPolygonFont::~FTGLPolygonFont()
{}


bool FTGLPolygonFont::MakeGlyphList()
{
	for( unsigned int n = 0; n < numGlyphs; ++n)
	{
		FT_Glyph ftGlyph = face.Glyph( n, FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP);
		
		tempGlyph = new FTPolyGlyph( ftGlyph, n);
		glyphList->Add( tempGlyph);
	}
	
	return !err;
}
