#include	"gl.h"

#include	"FTVectoriser.h"
#include	"FTGL.h"


FTContour::FTContour()
{	
	pointList.reserve( 1000); // FIXME magic number
}


FTContour::~FTContour()
{
	pointList.clear();
}


void FTContour::AddPoint( int x, int y)
{
	float fx, fy, fz;
	
	fx = static_cast<float>( x);
	fy = static_cast<float>( y);
	fy = 0;
	
	pointList.push_back( ftPoint( fx, fy, fz));

}


// De Casteljau algorithm supplied by Jed Soane
void FTVectoriser::deCasteljau( float t, int n)
{
    int i, k;

    //Calculating successive b(i)'s using de Casteljau algorithm.
    for ( i = 1; i <= n; i++)
        for (k = 0; k <= (n - i); k++)
        {
			bValues[i][k][0] = (1 - t) * bValues[i - 1][k][0] + t * bValues[i - 1][k + 1][0];
			bValues[i][k][1] = (1 - t) * bValues[i - 1][k][1] + t * bValues[i - 1][k + 1][1];
		}
		
    //Specify next vertex to be included on curve
	contour->AddPoint( bValues[n][0][0], bValues[n][0][1]);
}


void FTVectoriser::evaluateCurve( int n)
{
    int m, i;            					//loop counters
    float t;            					//parameter for curve point calc. [0.0, 1.0]
    float stepSize = 0.2;

    // setting the b(0) equal to the control points
    for (i = 0; i <= n; i++)
	{
		bValues[0][i][0] = ctrlPtArray[i][0];
		bValues[0][i][1] = ctrlPtArray[i][1];
    } //end for(i..)

    for (m = 0; m <= (1 / stepSize); m++)
    {
    	t = m * stepSize;
        deCasteljau( t, n);  //calls to evaluate point on curve att.
    } //end for(m...)
}


FTVectoriser::FTVectoriser( FT_Glyph glyph)
{
	FT_OutlineGlyph outline = (FT_OutlineGlyph)glyph;
	ftOutline = outline->outline;
	
	contourList.reserve( ftOutline.n_contours);
}


FTVectoriser::~FTVectoriser()
{
	for( int c = 0; c < contours(); ++c)
	{
		delete contourList[c];
	}

	contourList.clear();
}


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
			data[i] = contour->pointList[p].x / 64.0f; // is 64 correct?
			data[i + 1] = contour->pointList[p].y / 64.0f;
			data[i + 2] = contour->pointList[p].z / 64.0f;
			i += 3;
		}
	}
}
