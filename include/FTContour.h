#ifndef     __FTContour__
#define     __FTContour__

#include "FTPoint.h"
#include "FTVector.h"
#include "FTGL.h"


/**
 * FTContour class is a container of points that describe a vector font
 * outline. It is used as a container for the output of the bezier curve
 * evaluator in FTVectoriser.
 *
 * @see FTOutlineGlyph
 * @see FTPolyGlyph
 * @see FTPoint
 */
class FTGL_EXPORT FTContour
{
    public:
        /**
         * Constructor
         *
         * @param contour
         * @param pointTags
         * @param numberOfPoints
         */
        FTContour( FT_Vector* contour, char* pointTags, unsigned int numberOfPoints);

        /**
         * Destructor
         */
        ~FTContour()
        {
            pointList.clear();
        }

        /**
         * How many points define this contour
         *
         * @return the number of points in this contour
         */
        size_t size() const { return pointList.size();}
        
        /**
         * How many points define this contour
         *
         * @return the number of points in this contour
         */
        size_t Points() const { return size();}

        // FIXME make private
        /**
         *  The list of points in this contour
         */
        typedef FTVector<FTPoint> PointVector;
        PointVector pointList;
        
    private:
        /**
         * Add a point to this contour. This function tests for duplicate
         * points.
         *
         * @param point The point to be added to the contour.
         */
        inline void AddPoint( FTPoint point);
        
        /**
         * De Casteljau (bezier) algorithm contributed by Jed Soane
         *
         * @param curveOrder The order of the curve to be evaluated.
         * <code>2</code> equals conic (quadratic) and <code>3</code> equals cubic
         */
        inline void evaluateCurve( const int curveOrder);

        /**
         * 2D array storing values of de Casteljau algorithm.
         */
        float bValues[4][2];
};

#endif // __FTContour__
