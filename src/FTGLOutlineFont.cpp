#include	"FTGLOutlineFont.h"
#include	"FTGlyphContainer.h"
#include	"FTGL.h"
#include	"FTVectorGlyph.h"



FTGLOutlineFont::FTGLOutlineFont()
:	tempGlyph(0)
{}


FTGLOutlineFont::~FTGLOutlineFont()
{}


bool FTGLOutlineFont::MakeGlyphList()
{
	int glyphIndex;
	
	numGlyphs = 127;
	for( int n = 0; n < numGlyphs; ++n)
	{
		FT_Face* ftFace = face.Face();

		glyphIndex = FT_Get_Char_Index( *ftFace, n);
		
		err = FT_Load_Glyph( *ftFace, glyphIndex, FT_LOAD_DEFAULT);
		if( err)
		{ }

		FT_Glyph ftGlyph;
		
		err = FT_Get_Glyph( (*ftFace)->glyph, &ftGlyph);
		if( err)
		{}
		
		tempGlyph = new FTVectorGlyph( ftGlyph, glyphIndex);
		glyphList->Add( tempGlyph);
	}
}
