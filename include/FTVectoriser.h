#ifndef     __FTVectoriser__
#define     __FTVectoriser__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTPoint.h"
#include "FTVector.h"
#include "FTGL.h"


#ifndef CALLBACK
#define CALLBACK
#endif


/**
 * FTContour class is a container of points that describe a vector font
 * outline. It is mainly used as a container for the output of the bezier
 * curve evaluator in FTVectoriser.
 *
 * @see FTOutlineGlyph
 * @see FTPolyGlyph
 * @see FTPoint
 *
 */
class FTGL_EXPORT FTContour
{
    public:
        /**
         * Default constructor
         */
        FTContour()
        :   kMAXPOINTS( 1000)
        {   
            pointList.reserve( kMAXPOINTS);
        }

        /**
         *  Destructor
         */
        ~FTContour()
        {
            pointList.clear();
        }

        /**
         * Add a point to the end of this contour.
         *
         * Doesn't add the point if it's already on the end or the start
         * of the contour. The Z component is always 0
         *
         * @param x The X component of the point
         * @param y The Y component of the point
         */
        void AddPoint( const FTGL_DOUBLE x, const FTGL_DOUBLE y)
        {
            FTPoint point( x, y, 0.0f); 
            
            // Eliminate duplicate points.
            if( pointList.empty() || ( pointList[pointList.size() - 1] != point && pointList[0] != point))
            {
                pointList.push_back( point);
            }
        }

        /**
         * How many points define this contour
         *
         * @return the number of points in this contour
         */
        size_t size() const { return pointList.size();}

        /**
         *  The list of points in this contour
         */
        typedef FTVector<FTPoint> PointVector;
        PointVector pointList;
        
    private:
        /**
        * A 'max' number of points that this contour holds. Note however it
        * can hold more than this number. It is just used to reserve space
        * in the <vector>
        */
        const unsigned int kMAXPOINTS;
};


/**
 * FTTesselation captures points that are output by OpenGL's gluTesselator.
 */
class FTGL_EXPORT FTTesselation
{
    public:
        /**
         * Default constructor
         */
        FTTesselation()
        {
            pointList.reserve( 128);
        }

        /**
         *  Destructor
         */
        ~FTTesselation()
        {
            pointList.clear();
        }

        
        void AddPoint( const FTGL_DOUBLE x, const FTGL_DOUBLE y, const FTGL_DOUBLE z)
        {   
            pointList.push_back( FTPoint( x, y, z));
        }


        size_t size() const { return pointList.size();}

        GLenum meshType;
        typedef FTVector<FTPoint> PointVector;
        PointVector pointList;
        
    private:
        
};


/**
 * FTMesh is a container of FTTesselation's that make up a polygon glyph
 */
class FTGL_EXPORT FTMesh
{
    public:
        /**
         * Default constructor
         */
        FTMesh();

        /**
         *  Destructor
         */
        ~FTMesh();
        
        void AddPoint( const FTGL_DOUBLE x, const FTGL_DOUBLE y, const FTGL_DOUBLE z);
        void Begin( GLenum m);
        void End();
        void Error( GLenum e) { err = e;}
        
        FTGL_DOUBLE* Point();
        int size() const;
        
        /**
         * Get the GL ERROR returned by the glu tesselator
         */
        GLenum Error() const { return err;}

        typedef FTVector<FTPoint> PointVector;
        PointVector tempPool;
        
        typedef FTVector<FTTesselation*> TesselationVector;
        TesselationVector tess;
        
    protected:
    
    private:
        /**
         *  The list of points in this mesh
         */
        FTTesselation* tempTess;
        
        /**
         * GL ERROR returned by the glu tesselator
         */
        GLenum err;

};



/**
 * FTVectoriser class is a helper class that converts font outlines into
 * point data. It includes a bezier curve evaluator
 *
 * @see FTOutlineGlyph
 * @see FTPolyGlyph
 * @see FTContour
 * @see ftPoint
 *
 */
class FTGL_EXPORT FTVectoriser
{
    public:
        /**
         * Constructor
         *
         * @param glyph The freetype glyph to be processed
         */
        FTVectoriser( const FT_Glyph glyph);

        /**
         *  Destructor
         */
        virtual ~FTVectoriser();

        /**
         * Process the freetype outline data into contours of points
         *
         * @return <code>true</code> on success
         */
        bool Process();

        /**
         * Copy the outline data into a block of <code>FTGL_DOUBLEs</code>
         *
         * @param d a pointer to the memory to copy the data into.
         */
        void GetOutline( FTGL_DOUBLE* d);

        /**
         * Build an FTMesh from the vector outline data. 
         *
         * @param zNormal   The direction of the z axis of the normal
         *                  for this mesh
         */
        void MakeMesh( FTGL_DOUBLE zNormal = 1.0);
        
        /**
         * Copy the tesselation data into a block of <code>FTGL_DOUBLEs</code>
         *
         * @param d a pointer to the memory to copy the data into.
         */
        void GetMesh( FTGL_DOUBLE* d);
        
        /** Get the number of points in the tesselation
         *
         * @return the number of points.
         */
        size_t MeshPoints() const { return mesh->size();}
        
        /**
         * Get the total count of points in this outline
         *
         * @return the number of points
         */
        int points();

        /**
         * Get the count of contours in this outline
         *
         * @return the number of contours
         */
        size_t contours() const { return contourList.size();}

        /**
         * Get the nuber of points in a contour in this outline
         *
         * @param c     The contour index
         * @return      the number of points in contour[c]
         */
        size_t contourSize( int c) const { return contourList[c]->size();}

        /**
         * Get the flag for the tesselation rule for this outline
         *
         * @return The contour flag
         */
        int ContourFlag() const { return contourFlag;}
        
    private:
        /**
         * Process a conic ( second order) bezier curve.
         *
         * @param index The index of the current point in the point list.
         * @param first The index into the pointlist of the first point in
         *              the contour that the current point is part of.
         * @param last  The index into the pointlist of the last point in
         *              the contour that the current point is part of.
         * @return      the number of control points processed
         */
        int Conic( const int index, const int first, const int last);

        /**
         * Process a cubic ( third order) bezier curve
         *
         * @param index The index of the current point in the point list.
         * @param first The index into the pointlist of the first point in
         *              the contour that the current point is part of.
         * @param last  The index into the pointlist of the last point in
         *              the contour that the current point is part of.
         * @return      the number of control points processed
         */
        int Cubic( const int index, const int first, const int last);

        /**
         * @param t
         * @param n
         */
        inline void deCasteljau( const float t, const int n);

        /**
         * @param n
         */
        inline void evaluateCurve( const int n);

        /**
         * The list of contours in this outline
         */
        typedef FTVector<FTContour*> ContourVector;
        ContourVector contourList;
            
        /**
         * A Mesh for tesselations
         */
        FTContour* contour;
            
        /**
         * A Mesh for tesselations
         */
        FTMesh* mesh;

        /**
        * A flag indicating the tesselation rule for this outline
         */
        int contourFlag;

        /**
         * A Freetype outline
         */
        FT_Outline ftOutline;
        
        /**
         */
         // Magic numbers -- #define MAX_DEG 4
        float bValues[4][4][2];  //3D array storing values of de Casteljau algorithm.
        float ctrlPtArray[4][2]; // Magic numbers
        
        /**
         */
        const float kBSTEPSIZE;

};


#endif  //  __FTVectoriser__
