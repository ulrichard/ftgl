#include	"FTSize.h"
#include	"FTGL.h"


FTSize::FTSize()
:	size(0)
{}


FTSize::~FTSize()
{}


bool	FTSize::CharSize( FT_Face* ftFace, int point_size, int x_resolution, int y_resolution )
{
	size = point_size;
	err = FT_Set_Char_Size( *ftFace, 0L, point_size * 64, x_resolution, y_resolution);
	
	ftSize = (*ftFace)->size;
	
	return !err;
}


int	FTSize::Ascender() const
{
	return ftSize->metrics.ascender >> 6;
}


int	FTSize::Descender() const
{
	return ftSize->metrics.descender >> 6;
}


int	FTSize::Height() const
{
	return ftSize->metrics.height >> 6;
}


int	FTSize::Width() const
{
	return ftSize->metrics.max_advance >> 6;
}


int	FTSize::Underline() const
{
	return 0;
}


