#ifndef		__FTGlyphContainer__
#define		__FTGlyphContainer__

#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

//#include "FTGL.h"
class FTFace;
class FTGlyph;

using namespace std;

class	FTGlyphContainer
{
	public:
		// methods
		FTGlyphContainer( FTFace* face, int numGlyphs, bool p = false);
		~FTGlyphContainer();

		bool Add( FTGlyph* tempGlyph);

		FT_Vector& render( int index, int next, FT_Vector pen);
		
		// attributes
		
	private:
		// methods
		
		// attributes
		FT_Error err;
		bool preCache;
		int numGlyphs;
		FTFace* face;
		
		FT_Vector kernAdvance;
		float advance;

		
//		typedef pair<int, FTGlyph*> CHARREF; // glyphIndex, glyph
//		vector<CHARREF> glyphs;
//		map< int, FTGlyph*> CHARREF; // charCode, glyph
		vector<FTGlyph*> glyphs;
		
};


#endif	//	__FTGlyphContainer__
