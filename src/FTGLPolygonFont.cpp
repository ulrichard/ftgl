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
	FT_Face* ftFace = face.Face();
	int glyphIndex;
	
	// FIXME
	numGlyphs = 127;
	for( int n = 0; n < numGlyphs; ++n)
	{
		glyphIndex = FT_Get_Char_Index( *ftFace, n);
		
		err = FT_Load_Glyph( *ftFace, glyphIndex, FT_LOAD_DEFAULT);
		if( err)
		{ }

		FT_Glyph ftGlyph;
		
		err = FT_Get_Glyph( (*ftFace)->glyph, &ftGlyph);
		if( err)
		{}
		
		tempGlyph = new FTPolyGlyph( ftGlyph, glyphIndex);
		glyphList->Add( tempGlyph);
	}
}
