#include	"GL/gl.h"

#include	"FTGLTextureFont.h"
#include	"FTGlyphContainer.h"
#include	"FTGL.h"
#include	"FTTextureGlyph.h"


typedef unsigned long	UInt32; // a mac thing?


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
	textMem(0),
	padding(15),
	tempGlyph(0),
	maxTextSize(0),
	textureSize(0),
	glyphHeight(0),
	glyphWidth(0),
	horizGlyphs(0),
	vertGlyphs(0)

{}


FTGLTextureFont::~FTGLTextureFont()
{
	glDeleteTextures( 1, &glTextureID);
	delete [] textMem;
}


bool FTGLTextureFont::MakeGlyphList()
{
	FT_Face* ftFace = face.Face();
	
	CreateTexture();

	int currentTextX = padding;
	int currentTextY = padding + padding;
	
	float currTextU = (float)padding / (float)textureSize;
	float currTextV = (float)padding / (float)textureSize;
//	float Uinc = (float)glyphWidth / (float)textureSize;
//	float Vinc = (float)glyphHeight / (float)textureSize;
	
//	int currGlyph = 0;
	int glyphIndex;
	
	for( int n = 0; n <= numGlyphs; ++n)
	{
		glyphIndex = FT_Get_Char_Index( *ftFace, n);
		
		err = FT_Load_Glyph( *ftFace, glyphIndex, FT_LOAD_DEFAULT);
		if( err)
		{ }

		FT_Glyph ftGlyph;
		
		err = FT_Get_Glyph( (*ftFace)->glyph, &ftGlyph);
		if( err)
		{}
	
		unsigned char* data = textMem + ( ( currentTextY * textureSize) + currentTextX);
		
		currTextU = (float)currentTextX / (float)textureSize;
		
		tempGlyph = new FTTextureGlyph( ftGlyph, glyphIndex, data, textureSize, currTextU, currTextV);
		glyphList->Add( tempGlyph);
		
		currentTextX += glyphWidth;
		if( currentTextX > ( textureSize - glyphWidth))
		{
			currentTextY += glyphHeight;
			currentTextX = padding;
			currTextV = (float)currentTextY / (float)textureSize;
		}
	}

	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //What does this do exactly?
	glBindTexture( GL_TEXTURE_2D, glTextureID);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D( GL_TEXTURE_2D, 0, GL_ALPHA, textureSize, textureSize, 0, GL_ALPHA, GL_UNSIGNED_BYTE, textMem);

}


bool FTGLTextureFont::CreateTexture()
{
	glGetIntegerv( GL_MAX_TEXTURE_SIZE, &maxTextSize);
	glGenTextures( 1, &glTextureID);

	// calc the area required for this font
	glyphHeight = ( charSize.Height()) + padding;
	glyphWidth = ( charSize.Width()) + padding;
	
	//FIXME	
//	textureSize = 1024;
	int t;
	for( t = 64; t <= maxTextSize; t *=2)
	{		
		int h = static_cast<int>( t / glyphWidth);
		if( t > ( ( numGlyphs / h) * glyphHeight))
			break;
	}
	
	textureSize = t;
	
	horizGlyphs = static_cast<int>( textureSize / glyphWidth);
	vertGlyphs = static_cast<int>(( numGlyphs / horizGlyphs) + 1);
	
	// build the texture.
	textMem = new unsigned char[ textureSize * textureSize]; // GL_ALPHA texture;
	
	//FIXME
	for( int i = 0; i < ( textureSize * textureSize); ++i)
		textMem[i] = 0;
}


void FTGLTextureFont::render( const char* string)
{	
	glBindTexture( GL_TEXTURE_2D, glTextureID);
	
	// QUADS are faster!? Less function call overhead?
	glBegin( GL_QUADS);
		FTFont::render( string);
	glEnd();
}
