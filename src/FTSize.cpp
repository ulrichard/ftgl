#include	"FTSize.h"
#include	"FTGL.h"


FTSize::FTSize()
:	size(0)
{}


FTSize::~FTSize()
{}


bool	FTSize::CharSize( FT_Face* ftFace, int point_size, int x_resolution, int y_resolution )
{
	this->ftFace = ftFace;
	size = point_size;
	err = FT_Set_Char_Size( *ftFace, 0L, point_size * 64, x_resolution, y_resolution);
	
	ftSize = (*ftFace)->size;
	
	return !err;
}


float FTSize::Ascender() const
{
	return ftSize->metrics.ascender >> 6;
}


float FTSize::Descender() const
{
	return ftSize->metrics.descender >> 6;
}


float FTSize::Height() const
{
	if( FT_IS_SCALABLE((*ftFace)))
	{
		float height;
		if( FT_IS_SFNT((*ftFace))) // Don't think this is correct
		{
			height = (*ftFace)->bbox.yMax - (*ftFace)->bbox.yMin; // bbox.yMax-bbox.yMin
		}
		else
		{
			height = (*ftFace)->bbox.yMax - (*ftFace)->bbox.yMin >> 16; // bbox.yMax-bbox.yMin
		}

		height =  height * ( (float)ftSize->metrics.y_ppem / (float)(*ftFace)->units_per_EM);
		return height;
	}
	else
	{
		return ftSize->metrics.height >> 6;
	}
}


float FTSize::Width() const
{
	if( FT_IS_SCALABLE((*ftFace)))
	{
		float width;
		if( FT_IS_SFNT((*ftFace))) // Don't think this is correct
		{
			width = ((*ftFace)->bbox.xMax - (*ftFace)->bbox.xMin); // bbox.xMax-bbox.xMin
		}
		else
		{
			width = ((*ftFace)->bbox.xMax - (*ftFace)->bbox.xMin) >> 16; // bbox.xMax-bbox.xMin
		}
		
		width = width * ( (float)ftSize->metrics.x_ppem / (float)(*ftFace)->units_per_EM);
		return width;
	}
	else
	{
		return ftSize->metrics.max_advance >> 6;
	}
}


float FTSize::Underline() const
{
	return 0;
}
