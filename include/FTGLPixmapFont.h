#ifndef		__FTGLPixmapFont__
#define		__FTGLPixmapFont__


#include "FTGL.h"

#include "FTFont.h"

class FTPixmapGlyph;

/**
 * FTGLPixmapFont is a specialisation of the FTFont class for handling
 * Pixmap (Grey Scale) fonts
 *
 * @see		FTFont
 */
class FTGL_EXPORT FTGLPixmapFont : public FTFont
{
	public:
		// methods
		FTGLPixmapFont();
		~FTGLPixmapFont();
		
		void render( const char* string);
		void render( const wchar_t* string);


	private:
		// methods
		bool MakeGlyphList();
		
		// attributes
		FTPixmapGlyph* tempGlyph;
		
};


#endif	//	__FTGLPixmapFont__

