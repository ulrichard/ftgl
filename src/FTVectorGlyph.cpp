#include	"GL/gl.h"

#include	"FTVectorGlyph.h"
#include	"FTVectoriser.h"
#include	"FTGL.h"



FTVectorGlyph::FTVectorGlyph( FT_Glyph glyph, unsigned int gi)
:	FTGlyph(gi),
	vectoriser(0),
	numPoints(0),
	numContours(0),
	contourLength(0),
	data(0),
	glList(0)
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
			data = new double[ numPoints * 3];
			vectoriser->Output( data);
			
			advance = glyph->advance.x >> 16; // this is 6 in the freetype docs!!!!!!
		}
	
		delete vectoriser;
		
	    if ( ( numContours < 1) || ( numPoints < 3)) // check this
			return;
			
 		glList = glGenLists(1);
 		int d = 0;
 
 		glNewList( glList, GL_COMPILE);
 			for( int c = 0; c < numContours; ++c)
 			{
 				glBegin( GL_LINE_LOOP);
 				for( int p = 0; p < ( contourLength[c]); ++p)
 				{
 					glVertex2dv( data + d);
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
	delete [] contourLength;
}


float FTVectorGlyph::Render( const FT_Vector& pen)
{
	if( glList)
	{
		glTranslatef( pen.x + pos.x, pen.y, 0);
			glCallList( glList);
		glTranslatef( -pen.x + pos.x, -pen.y, 0);
	}
	
	return advance;
}




