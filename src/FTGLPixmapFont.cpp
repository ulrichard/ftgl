#include	"GL/gl.h"

#include	"FTGLPixmapFont.h"
#include	"FTGlyphContainer.h"
#include	"FTPixmapGlyph.h"


FTGLPixmapFont::FTGLPixmapFont()
:	tempGlyph(0)
{}


FTGLPixmapFont::~FTGLPixmapFont()
{}


// OPSignature: bool FTGlyphContainer:MakeGlyphList() 
bool FTGLPixmapFont::MakeGlyphList()
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

		tempGlyph = new FTPixmapGlyph( ftGlyph, c);
		glyphList->Add( tempGlyph);
	}
	
	return !err;
}


void FTGLPixmapFont::render( const char* string)
{	
	glPushAttrib( GL_ENABLE_BIT | GL_PIXEL_MODE_BIT);

	glEnable(GL_BLEND);
 	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	FTFont::render( string);

	glPopAttrib();

}
