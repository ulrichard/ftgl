#include	"assert.h"

#include	"FTFace.h"
#include	"FTLibrary.h"
#include	"FTGL.h"


// OPSignature:  FTFace:FTFace() 
FTFace::FTFace()
:	ftFace(0),
	numCharMaps(0),
	numGlyphs(0)
{
//Insert your own code here.

//End of user code.         
}


// OPSignature:  FTFace:~FTFace() 
FTFace::~FTFace()
{
	if( ftFace)
	{
		Close();
		delete ftFace; // is this a prob?
		ftFace = 0;
	}
}


// OPSignature: bool FTFace:open( const char*:filename  FONTTYPE:fontType ) 
bool	FTFace::Open( const char* filename)
{
	ftFace = new FT_Face;
	FT_Error err = FT_New_Face( *FTLibrary::Instance().GetLibrary(), filename, 0, ftFace);
	
	if( err == FT_Err_Unknown_File_Format)
    {
//      ... the font file could be opened and read, but it appears
//      ... that its font format is unsupported
		delete ftFace;
		ftFace = 0;
	    return false;
    }
    else if( err)
    {
//      ... another error code means that the font file could not
//      ... be opened or read, or simply that it is broken...
		delete ftFace;
		ftFace = 0;
	    return false;
    }
    
    return true;
}


// OPSignature: bool FTFace:open( const char*:filename  FONTTYPE:fontType ) 
void FTFace::Close()
{
	FT_Done_Face( *ftFace);
}


// OPSignature: bool FTFace:SetSize( const int:size  const int:res ) 
FTSize& FTFace::Size( const int size, const int res )
{
	charSize.CharSize( ftFace, size, res, res);
	return charSize;
}


// OPSignature: void FTFace:SetCharMap( CHARMAP:encoding ) 
bool FTFace::CharMap( CHARMAP encoding )
{
//Insert your own code here.

//End of user code.         
}


// OPSignature: FT_Glyph FTFace:GetGlyph( int:index ) 
FT_Glyph	FTFace::Glyph( int index )
{
//Insert your own code here.

//End of user code.         
}


// OPSignature: FT_Vector FTFace:GetKernAdvance( int:index1  int:index2 ) 
FT_Vector	FTFace::KernAdvance( int index1, int index2 )
{
//Insert your own code here.

//End of user code.         
}
