#ifndef		__FTGLOutlineFont__
#define		__FTGLOutlineFont__

#include "FTGL.h"

#include "FTFont.h"


class FTOutlineGlyph;

/**
 * FTGLOutlineFont is a specialisation of the FTFont class for handling
 * Vector Outline fonts
 *
 * @see		FTFont
 */
class FTGL_EXPORT FTGLOutlineFont : public FTFont
{
	public:
		// methods
		FTGLOutlineFont();
		~FTGLOutlineFont();
		
		void render( const char* string);
		void render( const wchar_t* string);

		// attributes
		
	private:
		// methods
		bool MakeGlyphList();
		
		// attributes
		FTOutlineGlyph* tempGlyph;
	
};
#endif // __FTGLOutlineFont__
