#ifndef		__FTSize__
#define		__FTSize__

#include <ft2build.h>
#include FT_FREETYPE_H

#include "FTGL.h"


class	FTSize
{
	public:
		// methods
		FTSize();
		virtual ~FTSize();
		bool CharSize( FT_Face* face, unsigned int point_size, unsigned int x_resolution, unsigned int y_resolution );
		int Ascender() const;
		int Descender() const;
		int Height() const;
		int Width() const;
		int Underline() const;

		FT_Error Error() const { return err; }
		
		// attributes
		
	private:
		// methods
		
		// attributes
		FT_Face* ftFace;
		FT_Size ftSize;
		unsigned int size;
		
		FT_Error err;
		
};

#endif	//	__FTSize__
