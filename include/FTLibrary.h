#ifndef		__FTLibrary__
#define		__FTLibrary__


#include <ft2build.h>
#include FT_FREETYPE_H
//#include FT_CACHE_H

#include "FTGL.h"


class	FTLibrary
{
	public:
		// methods
		static FTLibrary& Instance();
		FT_Library*	GetLibrary() const { return lib;}
		
		virtual FT_Error Error() const { return err;}
		
		virtual  ~FTLibrary();
		
		// attributes
		
	private:
		// methods
		FTLibrary();
		FTLibrary( const FT_Library&){}
		FTLibrary&	operator=( const FT_Library&){}
		bool Init();
		
		// attributes
		FT_Library*	lib;
//		FTC_Manager* manager;      /* the cache manager               */

		FT_Error err;

		
};
#endif	//	__FTLibrary__
