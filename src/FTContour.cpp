#include "FTContour.h"

static const unsigned int SECOND_ORDER_CURVE = 2;
static const unsigned int THIRD_ORDER_CURVE = 3;
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

                bValues[0][0][0] = previousPoint.x; bValues[0][0][1] = previousPoint.y;
                bValues[0][1][0] = controlPoint.x;  bValues[0][1][1] = controlPoint.y;
                bValues[0][2][0] = nextPoint.x;     bValues[0][2][1] = nextPoint.y;
                
                evaluateCurve( SECOND_ORDER_CURVE);
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
            
            bValues[0][0][0] = previousPoint.x; bValues[0][0][1] = previousPoint.y;
            bValues[0][1][0] = controlPoint.x;  bValues[0][1][1] = controlPoint.y;
            bValues[0][2][0] = nextPoint.x;     bValues[0][2][1] = nextPoint.y;
            
            evaluateCurve( SECOND_ORDER_CURVE);
            continue;
        }

        if( pointTag == FT_Curve_Tag_Cubic)
        {
            FTPoint controlPoint2 = nextPoint;
            
            FTPoint nextPoint = ( pointIndex == numberOfPoints - 2)
                                ? pointList[0]
                                : FTPoint( contour[pointIndex + 2]);
            
            bValues[0][0][0] = previousPoint.x; bValues[0][0][1] = previousPoint.y;
            bValues[0][1][0] = controlPoint.x;  bValues[0][1][1] = controlPoint.y;
            bValues[0][2][0] = controlPoint2.x; bValues[0][2][1] = controlPoint2.y;
            bValues[0][3][0] = nextPoint.x;     bValues[0][3][1] = nextPoint.y;
        
            evaluateCurve( THIRD_ORDER_CURVE);
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


void FTContour::deCasteljau( const float t, const int n)
{
    //Calculating successive b(i)'s using de Casteljau algorithm.
    for( int i = 1; i <= n; i++)
    {
        for( int k = 0; k <= (n - i); k++)
        {
            bValues[i][k][0] = (1 - t) * bValues[i - 1][k][0] + t * bValues[i - 1][k + 1][0];
            bValues[i][k][1] = (1 - t) * bValues[i - 1][k][1] + t * bValues[i - 1][k + 1][1];
        }
    }

    AddPoint( FTPoint( bValues[n][0][0], bValues[n][0][1], 0.0f));
}


void FTContour::evaluateCurve( const int n)
{
    float t; //parameter for curve point calc. [0.0, 1.0]

    for( int m = 0; m <= ( 1 / BEZIER_STEP_SIZE); m++)
    {
        t = m * BEZIER_STEP_SIZE;
        deCasteljau( t, n);  //calls to evaluate point on curve at t.
    }
}

