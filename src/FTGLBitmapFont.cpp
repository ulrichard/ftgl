#include	"GL/gl.h"

#include	"FTGLBitmapFont.h"
#include	"FTGlyphContainer.h"
#include	"FTBitmapGlyph.h"


FTGLBitmapFont::FTGLBitmapFont()
:	tempGlyph(0)
{}


FTGLBitmapFont::~FTGLBitmapFont()
{}


// OPSignature: bool FTGlyphContainer:MakeGlyphList() 
bool FTGLBitmapFont::MakeGlyphList()
{
//	if( preCache)

	FT_Face* ftFace = face.Face();
	
//	numGlyphs = 256; // FIXME hack
	
	for( unsigned int c = 0; c < numGlyphs; ++c)
	{
		err = FT_Load_Glyph( *ftFace, c, FT_LOAD_DEFAULT);
		FT_Glyph ftGlyph;
		
		err = FT_Get_Glyph( (*ftFace)->glyph, &ftGlyph);

//		FT_HAS_VERTICAL(face)

		tempGlyph = new FTBitmapGlyph( ftGlyph, c);
		glyphList->Add( tempGlyph);
	}
	
	return !err;
}


void FTGLBitmapFont::render( const char* string)
{	
	glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT);
	
	// doing this every frame is a bad?
	glPixelStorei( GL_UNPACK_LSB_FIRST, GL_FALSE);
	glPixelStorei( GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1);

	FTFont::render( string);

	glPopClientAttrib();

}
