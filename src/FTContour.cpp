#include "FTContour.h"

static const unsigned int SECOND_ORDER_CURVE = 2;
static const unsigned int THIRD_ORDER_CURVE = 3;


FTContour::FTContour( FT_Vector* contour, char* pointTags, unsigned int numberOfPoints)
:   kBSTEPSIZE( 0.2f)
{   
    FTVector<ContourPoint> tempPointList;
    
    for( unsigned int pointIndex = 0; pointIndex < numberOfPoints; ++ pointIndex)
    {
        if( pointIndex == numberOfPoints - 1)
        {
            if( pointTags[pointIndex] == FT_Curve_Tag_Conic && pointTags[0] == FT_Curve_Tag_Conic)
            {
                tempPointList.push_back( ContourPoint( FTPoint( contour[pointIndex]), pointTags[pointIndex]));
    
                FTPoint implicitPoint( static_cast<float>( contour[pointIndex].x + contour[0].x) * 0.5f,
                                       static_cast<float>( contour[pointIndex].y + contour[0].y) * 0.5f,
                                       0);
                tempPointList.push_back( ContourPoint( implicitPoint, FT_Curve_Tag_On));
            }
            else
            {
                tempPointList.push_back( ContourPoint( FTPoint( contour[pointIndex]), pointTags[pointIndex]));
            }
        }
        else if( pointTags[pointIndex] == FT_Curve_Tag_Conic && pointTags[pointIndex + 1] == FT_Curve_Tag_Conic)
        {
            tempPointList.push_back( ContourPoint( FTPoint( contour[pointIndex]), pointTags[pointIndex]));

            FTPoint implicitPoint( static_cast<float>( contour[pointIndex].x + contour[pointIndex + 1].x) * 0.5f,
                                   static_cast<float>( contour[pointIndex].y + contour[pointIndex + 1].y) * 0.5f,
                                   0);
            tempPointList.push_back( ContourPoint( implicitPoint, FT_Curve_Tag_On));
        }
        else
        {
            tempPointList.push_back( ContourPoint( FTPoint( contour[pointIndex]), pointTags[pointIndex]));
        }
    }

    for( unsigned int pointIndex = 0; pointIndex < tempPointList.size();)
    {
        switch( tempPointList[pointIndex].tag)
        {
            case FT_Curve_Tag_Conic:
                EvaluateConicCurve( pointIndex, tempPointList);
                ++pointIndex;
                break;
            case FT_Curve_Tag_Cubic:
                EvaluateCubicCurve( pointIndex, tempPointList);
                pointIndex += 2;
                break;
            case FT_Curve_Tag_On:
            default:
                AddPoint( tempPointList[pointIndex].point);
                ++pointIndex;
                break;
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


void FTContour::EvaluateConicCurve( const int index, const FTVector<ContourPoint>& pointList)
{
    unsigned int controlPoint = index;
    unsigned int startPoint = index -1;
    unsigned int endPoint = index + 1;
    
    if( 0 == controlPoint)
    {
        startPoint = pointList.size() - 1;
    }
    else if( pointList.size() - 1 == controlPoint)
    {
        endPoint = 0;
    }
    
    ctrlPtArray[0][0] = pointList[startPoint].point.x;   ctrlPtArray[0][1] = pointList[startPoint].point.y;
    ctrlPtArray[1][0] = pointList[controlPoint].point.x; ctrlPtArray[1][1] = pointList[controlPoint].point.y;
    ctrlPtArray[2][0] = pointList[endPoint].point.x;     ctrlPtArray[2][1] = pointList[endPoint].point.y;
    
    evaluateCurve( SECOND_ORDER_CURVE);
}


void FTContour::EvaluateCubicCurve( const int index, const FTVector<ContourPoint>& pointList)
{
    unsigned int controlPointOne = index;
    unsigned int controlPointTwo = index + 1;
    unsigned int startPoint = index -1;
    
    if( controlPointOne == pointList.size() - 1)
    {
        controlPointTwo = 0; 
    }
    
    unsigned int endPoint = controlPointTwo + 1;
    
    if( controlPointTwo == pointList.size() - 1)
    {
        endPoint = 0;
    }
    
    if( 0 == controlPointOne)
    {
        startPoint = pointList.size() - 1; 
    }

    ctrlPtArray[0][0] = pointList[startPoint].point.x;      ctrlPtArray[0][1] = pointList[startPoint].point.y;
    ctrlPtArray[1][0] = pointList[controlPointOne].point.x; ctrlPtArray[1][1] = pointList[controlPointOne].point.y;
    ctrlPtArray[2][0] = pointList[controlPointTwo].point.x; ctrlPtArray[2][1] = pointList[controlPointTwo].point.y;
    ctrlPtArray[3][0] = pointList[endPoint].point.x;        ctrlPtArray[3][1] = pointList[endPoint].point.y;

    evaluateCurve( THIRD_ORDER_CURVE);
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
       
    //Specify next vertex to be included on curve
    AddPoint( FTPoint( bValues[n][0][0], bValues[n][0][1], 0.0f));
}


void FTContour::evaluateCurve( const int n)
{
    // setting the b(0) equal to the control points
    for( int i = 0; i <= n; i++)
    {
        bValues[0][i][0] = ctrlPtArray[i][0];
        bValues[0][i][1] = ctrlPtArray[i][1];
    }

    float t; //parameter for curve point calc. [0.0, 1.0]

    for( int m = 0; m <= ( 1 / kBSTEPSIZE); m++)
    {
        t = m * kBSTEPSIZE;
        deCasteljau( t, n);  //calls to evaluate point on curve at t.
    }
}

