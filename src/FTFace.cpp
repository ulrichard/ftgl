#include	"FTFace.h"
#include	"FTLibrary.h"
#include	"FTGL.h"


FTFace::FTFace()
:	ftFace(0),
	numCharMaps(0),
	numGlyphs(0)
{}


FTFace::~FTFace()
{
	Close();
}


bool FTFace::Open( const char* filename)
{
	ftFace = new FT_Face;
	err = FT_New_Face( *FTLibrary::Instance().GetLibrary(), filename, 0, ftFace);

	if( err)
    {
		delete ftFace;
		ftFace = 0;
	    return false;
    }
    else
    {
		return true;
	}
}


void FTFace::Close()
{
	if( ftFace)
	{
		FT_Done_Face( *ftFace);
		delete ftFace; // is this a prob?
		ftFace = 0;
	}
}


FTSize& FTFace::Size( const unsigned int size, const unsigned int res )
{
	if( !charSize.CharSize( ftFace, size, res, res))
	{
		err = charSize.Error();
	}
	
	return charSize;
}


bool FTFace::CharMap( FT_Encoding encoding )
{
	
// 	FT_CharMap  found = 0;
//     FT_CharMap  charmap;
//     int         n;
// 
//     for ( n = 0; n < face->num_charmaps; n++ )
//     {
//       charmap = face->charmaps[n];
//       if ( charmap->platform_id == my_platform_id &&
//            charmap->encoding_id == my_encoding_id )
//       {
//         found = charmap;
//         break;
//       }
//     }
// 
//     if ( !found ) { ... }
// 
//     /* now, select the charmap for the face object */
//     error = FT_Set_CharMap( face, found );
//    if ( error ) { ... }


	err = FT_Select_Charmap( *ftFace, encoding );
	return !err;
}


unsigned int FTFace::CharIndex( unsigned int index ) const
{
	return FT_Get_Char_Index( *ftFace, index);
}


FT_Vector& FTFace::KernAdvance( unsigned int index1, unsigned int index2 )
{
	kernAdvance.x = 0; kernAdvance.y = 0;
	
	if( FT_HAS_KERNING((*ftFace)) && index1 && index2)
	{
		err = FT_Get_Kerning( *ftFace, index1, index2, ft_kerning_unfitted, &kernAdvance);
		if( !err)
		{	
			kernAdvance.x /= 64; kernAdvance.y /= 64;
		}
	}
	
	return kernAdvance;
}


FT_Glyph* FTFace::Glyph( unsigned int index, FT_Int load_flags)
{
	err = FT_Load_Glyph( *ftFace, index, load_flags);	
	err = FT_Get_Glyph( (*ftFace)->glyph, &ftGlyph);
		
	if( !err)
	{
		return &ftGlyph;
	}
	else
	{
		return NULL;
	}
}



