#include	"GL/gl.h"
#include	"GL/glu.h"

#include	"FTPolyGlyph.h"
#include	"FTVectoriser.h"
#include	"FTGL.h"


#ifndef CALLBACK
#define CALLBACK
#endif


void ftglError( GLenum errCode)
{
//	const GLubyte* estring;
//	estring = gluErrorString( errCode);
//	fprintf( stderr, "ERROR : %s\n", estring);
//	exit(1);
}

void ftglVertex( void* data)
{
	glVertex3dv( (double*)data);
}


void ftglBegin( GLenum type)
{
	glBegin( type);
}


void ftglEnd()
{
	glEnd();
}


void ftglCombine( GLdouble coords[3], void* vertex_data[4], GLfloat weight[4], void** outData)
{
	double* vertex = new double[3];
	
	vertex[0] = coords[0];
	vertex[1] = coords[1];
	vertex[2] = coords[2];

	*outData = vertex;
}


FTPolyGlyph::FTPolyGlyph( FT_Glyph glyph, int gi)
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
			
			contourFlag = vectoriser->contourFlag;
			advance = glyph->advance.x >> 16; // this is 6 in the freetype docs!!!!!!
		}
	
		delete vectoriser;

	    if ( ( numContours < 1) || ( numPoints < 3))
			return;

		Tesselate();
	}
}


void FTPolyGlyph::Tesselate()
{
	glList = glGenLists(1);
	GLUtesselator* tobj = gluNewTess();
	int d = 0;
	
	gluTessCallback( tobj, GLU_TESS_BEGIN, (void (CALLBACK*)())ftglBegin);
	gluTessCallback( tobj, GLU_TESS_VERTEX, (void (CALLBACK*)())ftglVertex);
	gluTessCallback( tobj, GLU_TESS_COMBINE, (void (CALLBACK*)())ftglCombine);
	gluTessCallback( tobj, GLU_TESS_END, ftglEnd);
	gluTessCallback( tobj, GLU_TESS_ERROR, (void (CALLBACK*)())ftglError);
	
	glNewList( glList, GL_COMPILE);
	
//		if( contourFlag & ft_outline_even_odd_fill) // ft_outline_reverse_fill
//		{
//			gluTessProperty( tobj, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_ODD);
//		}
//		else
//		{
//			gluTessProperty( tobj, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_NONZERO);
//		}
//		
		gluTessProperty( tobj, GLU_TESS_TOLERANCE, 0);
		gluTessBeginPolygon( tobj, NULL);
		
			for( int c = 0; c < numContours; ++c)
			{
				gluTessBeginContour( tobj);
					for( int p = 0; p < ( contourLength[c]); ++p)
					{
						gluTessVertex( tobj, data + d, data + d);
						d += 3;
					}
				gluTessEndContour( tobj);
			}
			
		gluTessEndPolygon( tobj);
		
	glEndList();

	gluDeleteTess( tobj);
}


FTPolyGlyph::~FTPolyGlyph()
{
	delete [] data;
	delete [] contourLength;
}


float FTPolyGlyph::Render( const FT_Vector& pen)
{
	glTranslatef( pen.x, pen.y, 0);
		glCallList( glList);	
	glTranslatef( -pen.x, -pen.y, 0);
	
	return advance;
}
