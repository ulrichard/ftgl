#ifndef		__FTGlyphContainer__
#define		__FTGlyphContainer__

#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

//#include "FTGL.h"

class FTGlyph;

using namespace std;

class	FTGlyphContainer
{
	public:
		// methods
		FTGlyphContainer( FT_Face* face, int numGlyphs, bool p = false);
		~FTGlyphContainer();

		bool Add( FTGlyph* tempGlyph);

		bool render( int index, int next = 0);
		
		// attributes
		
	private:
		// methods
//		bool	MakeGlyphList( FT_Face* face);
		
		// attributes
//		FONTTYPE fontType;
		bool preCache;
		int numGlyphs;
		FTGlyph* tempGlyph;
		FT_Face* face;
		
//		typedef pair<int, FTGlyph*> CHARREF;
//		vector<CHARREF> glyphs;
		vector<FTGlyph*> glyphs;
		
};


#endif	//	__FTGlyphContainer__
