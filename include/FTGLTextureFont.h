#ifndef		__FTGLTextureFont
#define		__FTGLTextureFont
#include	"FTFont.h"

#include "FTGL.h"

class	FTGLTextureFont : public FTFont
{
	public:
		// methods
		FTGLTextureFont();
		~FTGLTextureFont();
		
		bool CreateTexture();
		
		bool TextureSize();
		
		// attributes
		int textureSize;
		
		int glTextureID;
		unsigned char* textMem;
		
		int padding;
		
	private:
		// methods
		bool MakeGlyphList();
		
};
#endif
