#include	"gl.h"

#include	"FTVectorGlyph.h"
#include	"FTGL.h"


FTContour::FTContour()
{	
	pointList.reserve( 1000); // FIXME magic number
}


FTContour::~FTContour()
{}


void FTContour::AddPoint( int x, int y)
{
	float fx, fy;
	
	fx = static_cast<float>( x);
	fy = static_cast<float>( y);
	
	pointList.push_back( ftPoint( fx, fy));

}


//2.De Casteljau algorithm
void FTVectoriser::deCasteljau( GLfloat t, int n, GLfloat bValues[MAX_DEG][MAX_DEG][2])
{
    int i, k, l;

    //Calculating successive b(i)'s using de Casteljau algorithm.
    for ( i = 1; i <= n; i++)
        for (k = 0; k <= (n - i); k++)
            for (l = 0; l < 2; l++)
                bValues[i][k][l] = (1 - t) * bValues[i - 1][k][l] + t * bValues[i - 1][k + 1][l];

    //Specify next vertex to be included on curve
	contour->AddPoint( bValues[n][0][0], bValues[n][0][1]);
}


//3. calculates t value to be used in de Casteljau and displays curve
void FTVectoriser::evaluateCurve( int n)
{
    GLint m, i;            					//loop counters
    GLfloat t;            					//parameter for curve point calc. [0.0, 1.0]
    GLfloat bValues[MAX_DEG][MAX_DEG][2];	//3D array storing values
                                        	//of de Casteljau algorithm.
    GLfloat stepSize = 0.2;

    // setting the b(0) equal to the control points
    for (i = 0; i <= n; i++)  {
        for (m = 0; m < 2; m++)
            bValues[0][i][m] = ctrlPtArray[i][m];
    } //end for(i..)

    for (m = 0; m <= (1 / stepSize); m++)
    {
    	t = m * stepSize;
        deCasteljau( t, n, bValues);  //calls to evaluate point on curve att.
    } //end for(m...)
}


FTVectoriser::FTVectoriser( FT_Glyph glyph)
{
	FT_OutlineGlyph outline = (FT_OutlineGlyph)glyph;
	ftOutline = outline->outline;
	
	contourList.reserve( ftOutline.n_contours);
}


FTVectoriser::~FTVectoriser()
{}


int FTVectoriser::points()
{
	int s = 0;
	for( int c = 0; c < contours(); ++c)
	{
		s += contourList[c]->size();
	}
	
	return s;
}


bool FTVectoriser::Ingest()
{
    if ( ( ftOutline.n_contours < 1) || ( ftOutline.n_points < 1))
		return false;

	short first = 0;
	short cont = ftOutline.n_contours;
	
	for( short c = 0; c < cont; ++c)
	{
		contour = new FTContour;
		
		short last =  ftOutline.contours[c];

		for( short p = first; p <= last; ++p)
		{
			switch( ftOutline.tags[p])
			{
				case FT_Curve_Tag_Conic:
					p += Conic( p, first, last);
					break;
				case FT_Curve_Tag_Cubic:
					p += Cubic( p, first, last);
					break;
				case FT_Curve_Tag_On:
				default:
 					contour->AddPoint( ftOutline.points[p].x, ftOutline.points[p].y);
			}
		}
		
		contourList.push_back( contour);

		first = last + 1;
	}
	
	return true;

}


int FTVectoriser::Conic( int index, int first, int last)
{
	if( ftOutline.tags[index + 1] != FT_Curve_Tag_Conic)
	{
		if( index != first)
		{
			ctrlPtArray[0][0] = ftOutline.points[index-1].x;	ctrlPtArray[0][1] = ftOutline.points[index-1].y;
		}
		else
		{
			ctrlPtArray[0][0] = ftOutline.points[last].x;	ctrlPtArray[0][1] = ftOutline.points[last].y;
		}
	
		ctrlPtArray[1][0] = ftOutline.points[index].x;		ctrlPtArray[1][1] = ftOutline.points[index].y;
		
//		if( index != last)
//		{
//			ctrlPtArray[2][0] = ftOutline.points[index+1].x;	ctrlPtArray[2][1] = ftOutline.points[index+1].y;
//		}
//		else
//		{
//			ctrlPtArray[2][0] = ftOutline.points[first].x;	ctrlPtArray[2][1] = ftOutline.points[first].y;
//		}
		evaluateCurve( 2);
		return 1;
	}
	else
	{
		//create a phantom point
		float x = ( ftOutline.points[index].x + ftOutline.points[index+1].x) / 2;
		float y = ( ftOutline.points[index].y + ftOutline.points[index+1].y) / 2;
		
		// process first curve
		if( index != first)
		{
			ctrlPtArray[0][0] = ftOutline.points[index-1].x;	ctrlPtArray[0][1] = ftOutline.points[index-1].y;
		}
		else
		{
			ctrlPtArray[0][0] = ftOutline.points[last].x;	ctrlPtArray[0][1] = ftOutline.points[last].y;
		}
		
		ctrlPtArray[1][0] = ftOutline.points[index].x;		ctrlPtArray[1][1] = ftOutline.points[index].y;
		ctrlPtArray[2][0] = x;	ctrlPtArray[2][1] = y;
		evaluateCurve( 2);
		
		// process second curve
		ctrlPtArray[0][0] = x;	ctrlPtArray[0][1] = y;
		ctrlPtArray[1][0] = ftOutline.points[index + 1].x;		ctrlPtArray[1][1] = ftOutline.points[index + 1].y;
		
		if( index != last -1)
		{
			ctrlPtArray[2][0] = ftOutline.points[index+2].x;	ctrlPtArray[2][1] = ftOutline.points[index+2].y;
		}
		else
		{
			ctrlPtArray[2][0] = ftOutline.points[first].x;	ctrlPtArray[2][1] = ftOutline.points[first].y;
		}
		evaluateCurve( 2);
		
		return 2;
	}
}


int FTVectoriser::Cubic( int index, int first, int last)
{
	if( index != first)
	{
		ctrlPtArray[0][0] = ftOutline.points[index-1].x;	ctrlPtArray[0][1] = ftOutline.points[index-1].y;
	}
	else
	{
		ctrlPtArray[0][0] = ftOutline.points[last].x;	ctrlPtArray[0][1] = ftOutline.points[last].y;
	}
	
	ctrlPtArray[1][0] = ftOutline.points[index].x;		ctrlPtArray[1][1] = ftOutline.points[index].y;
	ctrlPtArray[2][0] = ftOutline.points[index + 1].x;		ctrlPtArray[2][1] = ftOutline.points[index + 1].y;
	if( index != last -1)
	{
		ctrlPtArray[3][0] = ftOutline.points[index+2].x;	ctrlPtArray[3][1] = ftOutline.points[index+2].y;
	}
	else
	{
		ctrlPtArray[3][0] = ftOutline.points[first].x;	ctrlPtArray[3][1] = ftOutline.points[first].y;
	}
	evaluateCurve( 3);
	return 2;
}


void FTVectoriser::Output( float* data)
{
	int i = 0;
	
	for( int c= 0; c < contours(); ++c)
	{
		FTContour* contour = contourList[c];
		
		for( int p = 0; p < contour->size(); ++p)
		{
			data[i] = contour->pointList[p].first / 64.0f;
			data[i + 1] = contour->pointList[p].second / 64.0f;
			i += 2;
		}
	}
}


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




