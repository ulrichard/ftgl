#ifndef		__FTGLTextureFont
#define		__FTGLTextureFont
#include	"FTFont.h"

#include "FTGL.h"

class FTTextureGlyph;

class	FTGLTextureFont : public FTFont
{
	public:
		// methods
		FTGLTextureFont();
		~FTGLTextureFont();
		
		bool TextureSize(){};
		
		bool render( const char* string);

		
	private:
		// attributes
		FTTextureGlyph* tempGlyph;
		
		long maxTextSize;
		int textureSize;
		
		unsigned long glTextureID;
		unsigned char* textMem;
		
		int glyphHeight;
		int glyphWidth;

		int horizGlyphs;
		int vertGlyphs;

		int padding;
		
		// methods
		bool MakeGlyphList();
		bool CreateTexture();
		
		
};
#endif
