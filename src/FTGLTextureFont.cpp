#include	"gl.h"

#include	"FTGLTextureFont.h"
#include	"FTGlyphContainer.h"
#include	"FTGL.h"


inline UInt32 NextPowerOf2( UInt32 in)
{
     in -= 1;

     in |= in >> 16;
     in |= in >> 8;
     in |= in >> 4;
     in |= in >> 2;
     in |= in >> 1;

     return in + 1;
}


FTGLTextureFont::FTGLTextureFont()
:	glTextureID(0),
	textMem(0)
{
	glGetIntegerv( GL_MAX_TEXTURE_SIZE, &maxTextSize);
	glGenTextures( 1, &glTextureID);

}


FTGLTextureFont::~FTGLTextureFont()
{
	glDeleteTextures( 1, &glTextureID);
	delete [] texMem;
}


bool FTGLTextureFont::CreateTexture()
{
	// calc the area required for this font
	int glyphHeight = ftFace->size->metrics-> + padding;
	int glyphWidth = ftFace->size->metrics-> + padding;
	
	// calc the smallest texture size to fit the glyphs
	// this is bit naff!!
	for(int s = 64; s < maxTextSize; s = s * s)
	{
		int size = s -padding - padding;
		horizGlyphs = static_cast<int>( size / glyphWidth);
		
		vertGlyphs = static_cast<int>( numGlyphs / horizGlyphs);
		
		if( vertGlyphs * glyphHeight < size)
			break;
	}

	vertGlyphs = static_cast<int>( ( textureSize - padding) / glyphHeight);
	horizGlyphs = static_cast<int>( ( textureSize - padding) / glyphWidth);
	
	// build the texture.
	textMem = unsigned char[ s * s]; // GL_ALPHA texture;
}


bool FTGLTextureFont::MakeGlyphList()
{
	FT_Face* ftFace = face.Face();
	
	CreateTexture();

	int currentTextX = padding;
	int currentTextY = padding;
	
	currGlyph = 0;
	
	for( int y = 0; y < horizGlyphs; ++y)
	{
		for( int x = 0; x < vertGlyphs; ++x)
		{

		}
	}
}






