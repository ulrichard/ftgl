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
			data = new float[ numPoints * 3];
			vectoriser->Output( data);
			
			advance = glyph->advance.x >> 16; // this is 6 in the freetype docs!!!!!!
		}
	
		delete vectoriser;
		
	    if ( ( numContours < 1) || ( numPoints < 1))
			return;
			
 		glList = glGenLists(1);
 		int d = 0;
 
 		glNewList( glList, GL_COMPILE);
 			for( int c = 0; c < numContours; ++c)
 			{
 				glBegin( GL_LINE_LOOP);
 				for( int p = 0; p < ( contourLength[c]); ++p)
 				{
 					glVertex2f( data[d], data[d + 1]);
 					d += 3;
 				}
 				glEnd();
 			}
 		glEndList();
	
	}
}


FTVectorGlyph::~FTVectorGlyph()
{
	delete [] data;
}


float FTVectorGlyph::Render( FT_Vector& pen)
{
	glTranslatef( pen.x, pen.y, 0);
		glCallList( glList);
	glTranslatef( -pen.x, -pen.y, 0);
	
	return advance;
}




