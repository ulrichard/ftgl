#include "FTContour.h"

static const unsigned int SECOND_DEGREE_CURVE = 2;
static const unsigned int THIRD_DEGREE_CURVE = 3;
static const float BEZIER_STEP_SIZE = 0.2f;


FTContour::FTContour( FT_Vector* contour, char* pointTags, unsigned int numberOfPoints)
{
    for( unsigned int pointIndex = 0; pointIndex < numberOfPoints; ++ pointIndex)
    {
        char pointTag = pointTags[pointIndex];
        
        if( pointTag == FT_Curve_Tag_On)
        {
            AddPoint( FTPoint( contour[pointIndex]));
            continue;
        }
        
        FTPoint controlPoint( contour[pointIndex]);
        FTPoint previousPoint = ( 0 == pointIndex)
                                ? FTPoint( contour[numberOfPoints - 1])
                                : pointList[pointList.size() - 1];

        FTPoint nextPoint = ( pointIndex == numberOfPoints - 1)
                            ? pointList[0]
                            : FTPoint( contour[pointIndex + 1]);

        if( pointTag == FT_Curve_Tag_Conic)
        {
            char nextPointTag = ( pointIndex == numberOfPoints - 1)
                                ? pointTags[0]
                                : pointTags[pointIndex + 1];
            
            while( nextPointTag == FT_Curve_Tag_Conic)
            {
                nextPoint = FTPoint( static_cast<float>( controlPoint.x + nextPoint.x) * 0.5f,
                                     static_cast<float>( controlPoint.y + nextPoint.y) * 0.5f,
                                     0);

                bValues[0][0] = previousPoint.x; bValues[0][1] = previousPoint.y;
                bValues[1][0] = controlPoint.x;  bValues[1][1] = controlPoint.y;
                bValues[2][0] = nextPoint.x;     bValues[2][1] = nextPoint.y;
                
                evaluateCurve( SECOND_DEGREE_CURVE);
                ++pointIndex;
                
                previousPoint = nextPoint;
                controlPoint = FTPoint( contour[pointIndex]);
                nextPoint = ( pointIndex == numberOfPoints - 1)
                            ? pointList[0]
                            : FTPoint( contour[pointIndex + 1]);
                nextPointTag = ( pointIndex == numberOfPoints - 1)
                               ? pointTags[0]
                               : pointTags[pointIndex + 1];
            }
            
            bValues[0][0] = previousPoint.x; bValues[0][1] = previousPoint.y;
            bValues[1][0] = controlPoint.x;  bValues[1][1] = controlPoint.y;
            bValues[2][0] = nextPoint.x;     bValues[2][1] = nextPoint.y;
            
            evaluateCurve( SECOND_DEGREE_CURVE);
            continue;
        }

        if( pointTag == FT_Curve_Tag_Cubic)
        {
            FTPoint controlPoint2 = nextPoint;
            
            FTPoint nextPoint = ( pointIndex == numberOfPoints - 2)
                                ? pointList[0]
                                : FTPoint( contour[pointIndex + 2]);
            
            bValues[0][0] = previousPoint.x; bValues[0][1] = previousPoint.y;
            bValues[1][0] = controlPoint.x;  bValues[1][1] = controlPoint.y;
            bValues[2][0] = controlPoint2.x; bValues[2][1] = controlPoint2.y;
            bValues[3][0] = nextPoint.x;     bValues[3][1] = nextPoint.y;
        
            evaluateCurve( THIRD_DEGREE_CURVE);
            ++pointIndex;
            continue;
        }
    }
}


void FTContour::AddPoint( FTPoint point)
{
    if( pointList.empty() || point != pointList[pointList.size() - 1])
    {
        pointList.push_back( point);
    }
}


void FTContour::evaluateCurve( const int curveDegree)
{
    for( unsigned int i = 0; i <= ( 1.0f / BEZIER_STEP_SIZE); i++)
    {
        float t = static_cast<float>(i) * BEZIER_STEP_SIZE;

        for( unsigned int m = curveDegree; m > 0; m--)
        {
            for ( unsigned int j = 0; j < m; j++)
            {
                bValues[j][0] = (1.0f - t) * bValues[j][0] + t * bValues[j + 1][0];
                bValues[j][1] = (1.0f - t) * bValues[j][1] + t * bValues[j + 1][1];
            }
        }

    	AddPoint( FTPoint( bValues[0][0], bValues[0][1], 0.0f));
    }
}

