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
	if( ftFace)
	{
		Close();
		delete ftFace; // is this a prob?
		ftFace = 0;
	}
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
	FT_Done_Face( *ftFace);
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
// 	ft_encoding_none, 0, 0, 0, 0
// 	ft_encoding_symbol,  's', 'y', 'm', 'b'
// 	ft_encoding_unicode, 'u', 'n', 'i', 'c'
// 	ft_encoding_latin_2, 'l', 'a', 't', '2'
// 	ft_encoding_sjis,    's', 'j', 'i', 's'
// 	ft_encoding_gb2312,  'g', 'b', ' ', ' '
// 	ft_encoding_big5,    'b', 'i', 'g', '5'
// 	ft_encoding_wansung, 'w', 'a', 'n', 's'
// 	ft_encoding_johab,   'j', 'o', 'h', 'a'
// 	ft_encoding_adobe_standard, 'A', 'D', 'O', 'B'
// 	ft_encoding_adobe_expert,   'A', 'D', 'B', 'E'
// 	ft_encoding_adobe_custom,   'A', 'D', 'B', 'C'
// 	ft_encoding_apple_roman, 'a', 'r', 'm', 'n'
	
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



