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


void FTGLOutlineFont::render( const char* string)
{	
	glPushAttrib( GL_ENABLE_BIT | GL_HINT_BIT | GL_LINE_BIT | GL_PIXEL_MODE_BIT);
	
	glEnable( GL_LINE_SMOOTH);
	glHint( GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glEnable(GL_BLEND);
 	glBlendFunc( GL_SRC_ALPHA, GL_ONE); // GL_ONE_MINUS_SRC_ALPHA

	FTFont::render( string);

	glPopAttrib();

}
