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
		bool CharSize( FT_Face* face, int point_size, int x_resolution, int y_resolution );
		int	Ascender() const;
		int	Descender() const;
		int	Height() const;
		int	Width() const;
		
		// attributes
		
	private:
		// methods
		
		// attributes
		FT_Size   ftSize;
		int	size;
		
};

#endif	//	__FTSize__
