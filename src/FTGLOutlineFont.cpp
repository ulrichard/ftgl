#include	"GL/gl.h"

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
//	int glyphIndex;
	FT_Face* ftFace = face.Face();
	
	numGlyphs = 127; // FIXME hack
	
	for( int n = 0; n < numGlyphs; ++n)
	{
		err = FT_Load_Glyph( *ftFace, n, FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP); // FT_LOAD_DEFAULT... FT_LOAD_NO_SCALE
		FT_Glyph ftGlyph;
		
		err = FT_Get_Glyph( (*ftFace)->glyph, &ftGlyph);
		
		tempGlyph = new FTVectorGlyph( ftGlyph, n);
		glyphList->Add( tempGlyph);
	}
	
	return !err;
}


void FTGLOutlineFont::render( const char* string)
{	
	glPushAttrib( GL_ENABLE_BIT | GL_HINT_BIT | GL_LINE_BIT | GL_PIXEL_MODE_BIT);
	
	glEnable( GL_LINE_SMOOTH);
	glHint( GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glEnable(GL_BLEND);
 	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // GL_ONE

	FTFont::render( string);

	glPopAttrib();

}
