#ifndef		__FTFont__
#define		__FTFont__

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "FTFace.h"

//#include "FTGL.h"


//class FTGlyph;
class FTGlyphContainer;

using namespace std;


class	FTFont
{
	public:
		// methods
		FTFont();
		virtual ~FTFont();
		virtual bool Open( const char* fontname );
		void Close();
		bool FaceSize( const int size, const int res = 72 );
		virtual bool CharMap( CHARMAP encoding );
//		virtual FTGlyph*	Glyph( unsigned char code );
//		virtual FTGlyph*	Glyph( unsigned char thisCode, unsigned char nextCode );
		int	Ascender() const;
		int	Descender() const;
		void	BBox( const char* text, int& llx, int& lly, int& urx, int& ury ) const;
		bool	render( const char* string );
		
		FT_Error Error() const { return err;}
		
		// attributes
		
	protected:
		// methods
		virtual bool MakeGlyphList() = 0;
		
		// attributes
		FT_Error err;
		
		// list of faces
		FTFace face;
		int	numFaces;
		
		// list of sizes
		FTSize charSize;
		
		int numGlyphs;
		
		string fontName;
		
		FTGlyphContainer*	glyphList;
		
	private:
		// methods
		
		// attributes
};


#endif	//	__FTFont__
