#include	"FTGlyph.h"


// OPSignature:  FTGlyph:FTGlyph( FT_Face:face  int:glyphIndex ) 
FTGlyph::FTGlyph()
:	advance(0),
	err(0)	
{
	pos.x = 0;
	pos.y = 0;
}


// OPSignature:  FTGlyph:~FTGlyph() 
FTGlyph::~FTGlyph()
{}
