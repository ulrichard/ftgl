#include	"FTVectorGlyph.h"
#include	"FTGL.h"


FTVectorGlyph::FTVectorGlyph( FT_Glyph glyph, int gi)
:	FTGlyph(gi)
{
//Insert your own code here.

//End of user code.         
}


FTVectorGlyph::~FTVectorGlyph()
{
//Insert your own code here.

//End of user code.         
}


float FTVectorGlyph::Render()
{
	return advance;
}
