#include	"FTFace.h"
#include	"FTFont.h"
#include	"FTGlyphContainer.h"
//#include	"FTGL.h"




// OPSignature:  FTFont:FTFont() 
FTFont::FTFont()
:	fontName(0),
	numFaces(0),
	glyphList(0)
{
	pen.x = 0;
	pen.y = 0;
}


// OPSignature:  FTFont:~FTFont() 
FTFont::~FTFont()
{
//Insert your own code here.

//End of user code.         
}


// OPSignature: bool FTFont:Open( const char*:fontname ) 
bool	FTFont::Open( const char* fontname )
{
	//FIXME first check map to see if it's already open.
//	FTFace face; // When we have a list of faces

	if( face.Open( fontname))
	{
//		faceList.insert( FaceMap::value_type( string( fontname), face));
		FT_Face* ftFace = face.Face();
		
		numGlyphs = (*ftFace)->num_glyphs;
		
		return true;
	}
	else
	{
		return false;
	}
	

}


// OPSignature: void FTFont:Close() 
void	FTFont::Close()
{
	face.Close();
	delete glyphList;
	
}


// OPSignature: bool FTFont:SetFaceSize( const int:size  const int:res ) 
bool FTFont::FaceSize( const int size, const int res )
{
	charSize = face.Size( size, res);

	if( glyphList)
		delete glyphList;
	
	glyphList = new FTGlyphContainer( face.Face(), numGlyphs);	
	
	MakeGlyphList();

	
	return true;
}

bool FTFont::CharMap( CHARMAP encoding)
{
	face.CharMap( encoding);
//	assert( face);

	//FIXME
	if( glyphList)
		delete glyphList;
		
	glyphList = new FTGlyphContainer( face.Face(), numGlyphs);
	
	MakeGlyphList();
}


//FTGlyph* FTFont::Glyph( unsigned char code )
//{}
//
//
//FTGlyph* FTFont::Glyph( unsigned char thisCode, unsigned char nextCode )
//{}


// OPSignature: int FTFont:getAscender() 
int	FTFont::Ascender() const
{
	return charSize.Ascender();
}


// OPSignature: int FTFont:getDescender() 
int	FTFont::Descender() const
{
	return charSize.Descender();
}


// OPSignature: void FTFont:getBBox( const char*:text  int&:llx  int&:lly  int&:urx  int&:ury ) 
void	FTFont::BBox( const char* text, int& llx, int& lly, int& urx, int& ury ) const
{
//Insert your own code here.

//End of user code.         
}


// OPSignature: bool FTFont:render( const char*:string ) 
bool FTFont::render( const char* string )
{
	char* c = string;
	FT_Vector kernAdvance;
	pen.x = 0; pen.y = 0;

	while( *c)
	{
		kernAdvance = glyphList->render( *c, *(c + 1), pen);
		
		pen.x += kernAdvance.x;
		pen.y += kernAdvance.y;
		
		++c;
	}
}
