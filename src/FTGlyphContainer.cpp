#include	"FTGlyphContainer.h"
#include	"FTGlyph.h"
//#include	"FTBitmapGlyph.h"
//#include	"FTPixmapGlyph.h"
//#include	"FTVectorGlyph.h"


FTGlyphContainer::FTGlyphContainer( FT_Face* f, int g, bool p)
:	preCache( p),
	numGlyphs(g),
	tempGlyph(0),
	face(f)
{
	glyphs.reserve( g);

//	numGlyphs = (*face)->num_glyphs;
	
//	MakeGlyphList( face);
}


// OPSignature:  FTGlyphContainer:~FTGlyphContainer() 
FTGlyphContainer::~FTGlyphContainer()
{
	vector<FTGlyph*>::iterator iter;
	for( iter = glyphs.begin(); iter != glyphs.end(); ++iter)
	{
		delete *iter;
	}
	
	glyphs.clear();
}


bool FTGlyphContainer::Add( FTGlyph* tempGlyph)
{
	glyphs.push_back( tempGlyph);
}


// OPSignature: bool FTGlyphContainer:MakeGlyphList() 
//bool FTGlyphContainer::MakeGlyphList( FT_Face* face)
//{
//	if( preCache)
//
//	glyphs.reserve( numGlyphs);
//
//	for( int c = 0; c < numGlyphs; ++c)
//	{
//		long glyphIndex = FT_Get_Char_Index( *face, c );
//		FT_Error err = FT_Load_Glyph( *face, glyphIndex, FT_LOAD_DEFAULT);
//		if( err)
//		{}
//
//		FT_Glyph ftglyph;
//		
//		err = FT_Get_Glyph( (*face)->glyph, &ftglyph);
//		if( err)
//		{}
//
//		FT_HAS_VERTICAL(face)
//
//		tempGlyph = new FTPixmapGlyph( ftglyph, glyphIndex);
//		glyphs.push_back( tempGlyph);
//		
//	}
//}


// OPSignature: bool FTGlyphContainer:render( int:index ) 
bool FTGlyphContainer::render( int index, int next)
{
	FT_Vector kernAdvance;
	kernAdvance.x = 0; kernAdvance.y = 0;
	
	if( index > glyphs.size())
		return false;
	
	if( 0 < next <=  glyphs.size())
	{
		FT_Error err = FT_Get_Kerning( *face, glyphs[index]->glyphIndex, glyphs[next]->glyphIndex, ft_kerning_default, &kernAdvance);
	}
	
//	glyphs[index].second->Render( kernAdvance);
	glyphs[index]->Render( kernAdvance);
}
