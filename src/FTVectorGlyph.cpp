#include	"gl.h"

#include	"FTVectorGlyph.h"
#include	"FTVectoriser.h"
#include	"FTGL.h"



FTVectorGlyph::FTVectorGlyph( FT_Glyph glyph, int gi)
:	FTGlyph(gi),
	vectoriser(0),
	numPoints(0),
	numContours(0),
	contourLength(0),
	data(0)
{
	if( glyph->format == ft_glyph_format_outline)
	{
		vectoriser = new FTVectoriser( glyph);
		
		if( vectoriser->Ingest())
		{
			numContours = vectoriser->contours();
			
			contourLength = new int[ numContours];
			
			for( int c = 0; c < numContours; ++c)
			{
				contourLength[c] = vectoriser->contourSize( c);
			}
			
			numPoints = vectoriser->points();
			data = new float[ numPoints * 2];
			vectoriser->Output( data);
			
			advance = glyph->advance.x >> 16; // this is 6 in the freetype docs!!!!!!
		}
	
		delete vectoriser;
	}
}


FTVectorGlyph::~FTVectorGlyph()
{
	delete [] data;
}


float FTVectorGlyph::Render( FT_Vector& pen)
{
	int d = 0;
	
	for( int c = 0; c < numContours; ++c)
	{
//		switch(c)
//		{
//			case 0:
//				glColor3f( 1.0, 0.0, 0.0);
//				break;
//			case 1:
//				glColor3f( 0.0, 1.0, 0.0);
//				break;
//			case 2:
//				glColor3f( 0.0, 0.0, 1.0);
//				break;
//			case 3:
//				glColor3f( 1.0, 1.0, 0.0);
//				break;
//		}
		
		glBegin( GL_LINE_LOOP);
			for( int p = 0; p < ( contourLength[c] * 2); p += 2)
			{
				glVertex2f( data[d] + pen.x, data[d + 1] + pen.y);
				
				d += 2;
			}
		glEnd();
	}
	
	return advance;
}




