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
	long glyphIndex;
	
	for( int c = 0; c < numGlyphs; ++c)
	{
		glyphIndex = FT_Get_Char_Index( *ftFace, c );
		
		err = FT_Load_Glyph( *ftFace, glyphIndex, FT_LOAD_DEFAULT);
		if( err)
		{ }

		FT_Glyph ftGlyph;
		
		err = FT_Get_Glyph( (*ftFace)->glyph, &ftGlyph);
		if( err)
		{}

//		FT_HAS_VERTICAL(face)

		tempGlyph = new FTPixmapGlyph( ftGlyph, glyphIndex);
		glyphList->Add( tempGlyph);
		
	}
}