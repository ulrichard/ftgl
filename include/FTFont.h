#ifndef		__FTFont__
#define		__FTFont__

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "FTFace.h"

#include "FTGL.h"


class FTGlyphContainer;

using namespace std;


class	FTFont
{
	public:
		// methods
		FTFont();
		virtual ~FTFont();
		virtual bool Open( const char* fontname );
		virtual void Close();
		virtual bool FaceSize( const int size, const int res = 72 );
		virtual bool CharMap( CHARMAP encoding );
		virtual int	Ascender() const;
		virtual int	Descender() const;
		virtual void BBox( const char* text, int& llx, int& lly, int& urx, int& ury ) const;
		virtual void render( const char* string );
		
		virtual FT_Error Error() const { return err;}
		
		// attributes
		
	protected:
		// methods
		virtual bool MakeGlyphList() = 0;
		
		// attributes
		FT_Error err;
		
		// future list of faces
		FTFace face;
		int	numFaces;
		
		// future list of sizes
		FTSize charSize;
		
		int numGlyphs;
		
		string fontName;
		
		FTGlyphContainer*	glyphList;
		
		FT_Vector pen;
		
	private:
		// methods
		
		// attributes
};


#endif	//	__FTFont__
