#ifndef     __FTPoint__
#define     __FTPoint__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTGL.h"

/**
 * FTPoint class is a basic 3 dimensional point or vector.
 */
class FTGL_EXPORT FTPoint
{
    public:
        /**
         * Default constructor. Point is set to zero.
         */
        FTPoint()
        {
            elements[0] = 0;
            elements[1] = 0;
            elements[2] = 0;
        }
        
        /**
         * Constructor.
         *
         * @param X
         * @param Y
         * @param Z
         */
        FTPoint( const FTGL_DOUBLE x, const FTGL_DOUBLE y, const FTGL_DOUBLE z)
        {
            elements[0] = x;
            elements[1] = y;
            elements[2] = z;
        }
        
        /**
         * Constructor. This converts an FT_Vector to an FT_Point
         *
         * @param ft_vector A freetype vector
         */
        FTPoint( const FT_Vector& ft_vector)
        {
            elements[0] = ft_vector.x;
            elements[1] = ft_vector.y;
            elements[2] = 0;
        }
        
        /**
         * Operator +=
         *
         * @param point
         * @return this plus point.
         */
        FTPoint& operator += ( const FTPoint& point)
        {
            elements[0] += point.elements[0];
            elements[1] += point.elements[1];
            elements[2] += point.elements[2];

            return *this;
        }

        /**
         * Operator == Tests for eqaulity
         *
         * @param a
         * @param b
         * @return
         */
        friend bool operator == ( const FTPoint &a, const FTPoint &b);

        /**
         * Operator != Tests for non equality
         *
         * @param a
         * @param b
         * @return
         */
        friend bool operator != ( const FTPoint &a, const FTPoint &b);
        
        
        /**
         * Cast to FTGL_DOUBLE*
         */
        operator FTGL_DOUBLE*()
        {
            return elements;
        }
        

        /**
         * Setters
         */
        void X( FTGL_DOUBLE x) { elements[0] = x;};
        void Y( FTGL_DOUBLE y) { elements[1] = y;};
        void Z( FTGL_DOUBLE z) { elements[2] = z;};


        /**
         * Getters
         */
        FTGL_DOUBLE X() const { return elements[0];};
        FTGL_DOUBLE Y() const { return elements[1];};
        FTGL_DOUBLE Z() const { return elements[2];};
        
    private:
        /**
         * The point data
         */
        FTGL_DOUBLE elements[3];
};

#endif  //  __FTPoint__

