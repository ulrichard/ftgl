#include	"FTLibrary.h"
#include	"FTGL.h"


// OPSignature: FTLibrary& FTLibrary:Instance() 
FTLibrary&	FTLibrary::Instance()
{
	static FTLibrary ftlib;
	return ftlib;
}


// OPSignature:  FTLibrary:~FTLibrary() 
FTLibrary::~FTLibrary()
{
	if( lib != 0)
	{
		FT_Done_FreeType( *lib);

		delete lib;
		lib= 0;
	}

//	if( manager != 0)
//	{
//		FTC_Manager_Done( manager );
//
//		delete manager;
//		manager= 0;
//	}
}


// OPSignature:  FTLibrary:FTLibrary() 
FTLibrary::FTLibrary()
: lib(0)
{
	Init();
}


// OPSignature: bool FTLibrary:Init() 
bool	FTLibrary::Init()
{
	if( lib != 0 )
		return true;

	lib = new FT_Library;

	if( FT_Init_FreeType( lib)) // false = no error
	{
		delete lib;
		lib= 0;
		return false;
	}
	
// 	FTC_Manager* manager;
// 	
// 	if( FTC_Manager_New( lib, 0, 0, 0, my_face_requester, 0, manager )
// 	{
// 		delete manager;
// 		manager= 0;
// 		return false;
// 	}


	return true;
}
