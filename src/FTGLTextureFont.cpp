#include	"gl.h"

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
	padding(15)
{
//	glGetIntegerv( GL_MAX_TEXTURE_SIZE, &maxTextSize);
//	glGenTextures( 1, &glTextureID);

}


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
	float Uinc = (float)glyphWidth / (float)textureSize;
	float Vinc = (float)glyphHeight / (float)textureSize;
	
	int currGlyph = 0;
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
	
	// calc the smallest texture size to fit the glyphs
//FIXME
//		     x * y
//		o = --------
//		     x + y
//	int x = glyphWidth * numGlyphs;
//	int y = glyphHeight * numGlyphs;
	
//	int o = ( x * y) / ( x + y);
	
//	textureSize = NextPowerOf2( o);
	
	textureSize = 1024;
		
	horizGlyphs = static_cast<int>( textureSize / glyphWidth);
	vertGlyphs = static_cast<int>(( numGlyphs / horizGlyphs) + 1);
	
	// build the texture.
	textMem = new unsigned char[ textureSize * textureSize]; // GL_ALPHA texture;
	
	//FIXME
	for( int i = 0; i < ( textureSize * textureSize); ++i)
		textMem[i] = 0;
}


bool FTGLTextureFont::render( const char* string)
{
	char* c = string;
	FT_Vector kernAdvance;
	pen.x = 0; pen.y = 0;
	
	glBindTexture( GL_TEXTURE_2D, glTextureID);
	glBegin( GL_QUADS);
	
	while( *c)
	{
		kernAdvance = glyphList->render( *c, *(c + 1), pen);
		
		pen.x += kernAdvance.x;
		pen.y += kernAdvance.y;
		
		++c;
	}

	glEnd();
}



