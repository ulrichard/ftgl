#ifndef		__FTGLTextureFont__
#define		__FTGLTextureFont__
#include	"FTFont.h"

#include "FTGL.h"

class FTTextureGlyph;

class	FTGLTextureFont : public FTFont
{
	public:
		// methods
		FTGLTextureFont();
		~FTGLTextureFont();
		
		bool TextureSize() const { return textureSize;}
		
		void render( const char* string);

		
	private:
		// attributes
		FTTextureGlyph* tempGlyph;
		
//		long maxTextSize;
		int maxTextSize; // For IRIX
		int textureSize;
		
//		unsigned long glTextureID;
		unsigned int glTextureID; // For IRIX
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
#endif    //    __FTGLTextureFont__
