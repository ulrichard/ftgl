#include	"FTFace.h"
#include	"FTFont.h"
#include	"FTGlyphContainer.h"
#include	"FTGlyph.h" // for FTBbox
#include	"FTGL.h"


FTFont::FTFont()
:	numFaces(0),
	glyphList(0),
	numGlyphs(0),
	preCache(true),
	err(0)
{
	pen.x = 0;
	pen.y = 0;
}


FTFont::~FTFont()
{
	Close();
}


bool FTFont::Open( const char* fontname, bool p)
{
	preCache = p;
	
	if( face.Open( fontname))
	{
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
	delete glyphList;
}


bool FTFont::FaceSize( const unsigned int size, const unsigned int res )
{
	charSize = face.Size( size, res);

	if( glyphList)
		delete glyphList;
	
	glyphList = new FTGlyphContainer( &face, numGlyphs, preCache);
	
	if( MakeGlyphList())
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool FTFont::MakeGlyphList()
{
	for( unsigned int c = 0; c < numGlyphs; ++c)
	{
		if( preCache)
		{
			glyphList->Add( MakeGlyph( c), c);
		}
		else
		{
			glyphList->Add( NULL, c);
		}
	}
	
	return !err;
}


bool FTFont::CharMap( FT_Encoding encoding)
{
	err = face.CharMap( encoding);
	return !err;
}


int	FTFont::Ascender() const
{
	return charSize.Ascender();
}


int	FTFont::Descender() const
{
	return charSize.Descender();
}


void FTFont::BBox( const char* string,
                   int& llx, int& lly, int& llz, int& urx, int& ury, int& urz)
{
	const unsigned char* c = (unsigned char*)string; // This is ugly, what is the c++ way?
	llx = lly = llz = urx = ury = urz = 0;
	FTBBox bbox;
 
	while( *c)
	{
		if( !glyphList->Glyph( static_cast<unsigned int>(*c)))
		{
			unsigned int g = face.CharIndex( static_cast<unsigned int>(*c));
			glyphList->Add( MakeGlyph( g), g);
		}
		
		bbox = glyphList->BBox( *c);
		
		// Lower extent
		lly = lly < bbox.y1 ? lly: bbox.y1;
		// Upper extent
		ury = ury > bbox.y2 ? ury: bbox.y2;
		// Depth
		urz = urz < bbox.z2 ? urz: bbox.z2;

		// Width
		urx += glyphList->Advance( *c, *(c + 1));
		++c;
	}
	
	//Final adjustments
	llx = glyphList->BBox( *string).x1;
	urx -= glyphList->Advance( *(c - 1), 0);
	urx += bbox.x2;

}

void FTFont::BBox( const wchar_t* string,
                   int& llx, int& lly, int& llz, int& urx, int& ury, int& urz)
{
	const wchar_t* c = string; // wchar_t IS unsigned?
	llx = lly = llz = urx = ury = urz = 0;
	FTBBox bbox;
 
	while( *c)
	{
		if( !glyphList->Glyph( static_cast<unsigned int>(*c)))
		{
			unsigned int g = face.CharIndex( static_cast<unsigned int>(*c));
			glyphList->Add( MakeGlyph( g), g);
		}
		
		bbox = glyphList->BBox( *c);
		
		// Lower extent
		lly = lly < bbox.y1 ? lly: bbox.y1;
		// Upper extent
		ury = ury > bbox.y2 ? ury: bbox.y2;
		// Depth
		urz = urz < bbox.z2 ? urz: bbox.z2;

		// Width
		urx += glyphList->Advance( *c, *(c + 1));
		++c;
	}
	
	//Final adjustments
	llx = glyphList->BBox( *string).x1;
	urx -= glyphList->Advance( *(c - 1), 0);
	urx += bbox.x2;

}


float FTFont::Advance( const wchar_t* string)
{
	const wchar_t* c = string; // wchar_t IS unsigned?
	float width = 0;

	while( *c)
	{
		if( !glyphList->Glyph( static_cast<unsigned int>(*c)))
		{
			unsigned int g = face.CharIndex( static_cast<unsigned int>(*c));
			glyphList->Add( MakeGlyph( g), g);
		}

		width += glyphList->Advance( *c, *(c + 1));	
		++c;
	}

	return width;
}


float FTFont::Advance( const char* string)
{
	const unsigned char* c = (unsigned char*)string; // This is ugly, what is the c++ way?
	float width = 0;

	while( *c)
	{
		if( !glyphList->Glyph( static_cast<unsigned int>(*c)))
		{
			unsigned int g = face.CharIndex( static_cast<unsigned int>(*c));
			glyphList->Add( MakeGlyph( g), g);
		}

		width += glyphList->Advance( *c, *(c + 1));
		++c;
	}

	return width;
}


void FTFont::render( const char* string )
{
	const unsigned char* c = (unsigned char*)string; // This is ugly, what is the c++ way?
	FT_Vector kernAdvance;
	pen.x = 0; pen.y = 0;

	while( *c)
	{
		if( !glyphList->Glyph( static_cast<unsigned int>(*c)))
		{
			unsigned int g = face.CharIndex( static_cast<unsigned int>(*c));
			glyphList->Add( MakeGlyph( g), g);
		}

		kernAdvance = glyphList->render( *c, *(c + 1), pen);
		
		pen.x += kernAdvance.x;
		pen.y += kernAdvance.y;
		++c;
	}
}


void FTFont::render( const wchar_t* string )
{
	const wchar_t* c = string; // wchar_t IS unsigned?
	FT_Vector kernAdvance;
	pen.x = 0; pen.y = 0;

	while( *c)
	{
		if( !glyphList->Glyph( static_cast<unsigned int>(*c)))
		{
			unsigned int g = face.CharIndex( static_cast<unsigned int>(*c));
			glyphList->Add( MakeGlyph( g), g);
		}

		kernAdvance = glyphList->render( *c, *(c + 1), pen);
		
		pen.x += kernAdvance.x;
		pen.y += kernAdvance.y;
		++c;
	}
}

