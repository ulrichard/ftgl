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

/**
 * FTGlyphContainer
 *
 * @see FTGlyph
 */
class	FTGlyphContainer
{
	public:
		// methods

		/**
		 * Constructor
		 */
		FTGlyphContainer( FTFace* face, int numGlyphs, bool p = false);

		/**
		 * Destructor
		 */
		~FTGlyphContainer();

		/**
		 * Adds a glyph to this glyph list.
		 *
		 * @param glyph		
		 * @return			<code>true</code>
		 */
		bool Add( FTGlyph* glyph);

		/**
		 * renders a character
		 */
		FT_Vector& render( unsigned int index, unsigned int next, FT_Vector pen);
		
		// attributes
		
	private:
		// methods
		
		// attributes

		/**
		 *
		 */
		FT_Error err;

		/**
		 *
		 */
		bool preCache;

		/**
		 *
		 */
		int numGlyphs;

		/**
		 *
		 */
		FTFace* face;
		

		/**
		 *
		 */
		FT_Vector kernAdvance;

		/**
		 *
		 */
		float advance;

		/**
		 *
		 */
		vector<FTGlyph*> glyphs;
//		typedef pair<int, FTGlyph*> CHARREF; // glyphIndex, glyph
//		vector<CHARREF> glyphs;
//		map< int, FTGlyph*> CHARREF; // charCode, glyph
		
};


#endif	//	__FTGlyphContainer__
