#include "FTFace.h"
#include "FTCharmap.h"


FTCharmap::FTCharmap( FTFace* face)
:   fontEncodingList(0),
    ftFace( *(face->Face())),
    err(0)
{
    if( !ftFace->charmap)
    {
        err = FT_Set_Charmap( ftFace, ftFace->charmaps[0]);
    }
    
    ftEncoding = ftFace->charmap->encoding;
}


FTCharmap::~FTCharmap()
{
    charMap.clear();
}


bool FTCharmap::CharMap( FT_Encoding encoding)
{
    if( ftEncoding == encoding)
    {
        return true;
    }
    
    err = FT_Select_Charmap( ftFace, encoding );
    
    if( !err)
    {
        ftEncoding = encoding;
    }
    else
    {
        ftEncoding = ft_encoding_none;
    }
        
    charMap.clear();
    return !err;
}


unsigned int FTCharmap::CharMapCount()
{
    return ftFace->num_charmaps;
}


FT_Encoding* FTCharmap::CharMapList()
{
    if( 0 == fontEncodingList)
    {
        fontEncodingList = new FT_Encoding[CharMapCount()];
        for( size_t encodingIndex = 0; encodingIndex < CharMapCount(); ++encodingIndex)
        {
            fontEncodingList[encodingIndex] = ftFace->charmaps[encodingIndex]->encoding;
        }
    }
    
    return fontEncodingList;
}


unsigned int FTCharmap::CharIndex( unsigned int characterCode )
{
    return charMap.find( characterCode);
}


void FTCharmap::InsertIndex( const unsigned int characterCode, const unsigned int containerIndex)
{
    charMap.insert( characterCode, containerIndex);
}


unsigned int FTCharmap::GlyphIndex( const unsigned int characterCode)
{
    unsigned int glyphIndex = FT_Get_Char_Index( ftFace, characterCode);
    return glyphIndex;
}
