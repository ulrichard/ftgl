#include	"gl.h"

#include	"FTGLPolygonFont.h"
#include	"FTGlyphContainer.h"
#include	"FTGL.h"
#include	"FTPolyGlyph.h"



FTGLPolygonFont::FTGLPolygonFont()
//Insert your own initialization here.

//End of user initialization.         
{
//Insert your own code here.

//End of user code.         
}


FTGLPolygonFont::~FTGLPolygonFont()
{
//Insert your own code here.

//End of user code.         
}


bool FTGLPolygonFont::MakeGlyphList()
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
		
		tempGlyph = new FTPolyGlyph( ftGlyph, glyphIndex);
		glyphList->Add( tempGlyph);
	}
}
