#include	"FTFace.h"
#include	"FTFont.h"
#include	"FTGlyphContainer.h"
#include	"FTGL.h"


FTFont::FTFont()
:	numFaces(0),
	glyphList(0),
	err(0)
{
	pen.x = 0;
	pen.y = 0;
}


FTFont::~FTFont()
{
	Close();
}


bool FTFont::Open( const char* fontname )
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
		err = face.Error();
		return false;
	}
}


void FTFont::Close()
{
	face.Close();
	delete glyphList;
}


bool FTFont::FaceSize( const int size, const int res )
{
	charSize = face.Size( size, res);

	if( glyphList)
		delete glyphList;
	
	glyphList = new FTGlyphContainer( face.Face(), numGlyphs);	
	
	if( MakeGlyphList())
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool FTFont::CharMap( CHARMAP encoding)
{
	face.CharMap( encoding);
	return false; // for the moment seeing as this doesn't do anything!!!
}


int	FTFont::Ascender() const
{
	return charSize.Ascender();
}


int	FTFont::Descender() const
{
	return charSize.Descender();
}


void FTFont::BBox( const char* text, int& llx, int& lly, int& urx, int& ury ) const
{
//Insert your own code here.

//End of user code.         
}


void FTFont::render( const char* string )
{
	const unsigned char* c = (unsigned char*)string; // This is ugly, what is the c++ way?
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
