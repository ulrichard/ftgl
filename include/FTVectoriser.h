#ifndef		__FTVectoriser__
#define		__FTVectoriser__

#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTGlyph.h"


// template < typename T>
// class ftLoop
// {
// 	public:	
// 		ftLoop();
// 		~ftLoop()
// 		{
// 			list.clear();
// 		}
// 		
// 		T& operator [] (unsigned int i)
// 		{
// 			int x = i;
// 			if( i < 0)
// 				x = i + list.size();
// 			
// 			if( i > list.size())
// 				x = i % list.size();
// 			
// 			return list[x];
// 		}
// 		
// 		void push_back( T t)
// 		{
// 			list.push_back(t);
// 		}
// 		
// 	private:
// 		vector<T> list;
// };


class ftPoint
{
	public:
		ftPoint()
		: x(0), y(0), z(0){}
		
		ftPoint( float X, float Y, float Z)
		: x(X), y(Y), z(Z){}
		
		friend bool operator == (const ftPoint &a, const ftPoint &b)
		{
			return((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
		}

		friend bool operator != (const ftPoint &a, const ftPoint &b)
		{
			return((a.x != b.x) || (a.y != b.y) || (a.z != b.z));
		}
		
		float x, y, z;
		
	private:
};


class FTContour
{
	public:
		// methods
		FTContour();
		~FTContour();
	
		void AddPoint( int x, int y);
		
		int size() const { return pointList.size();}

		// attributes
		vector< ftPoint> pointList;
		float ctrlPtArray[4][2];
		
	private:
		// methods

		// attributes
};


class FTVectoriser
{
	public:
		// methods
		FTVectoriser( FT_Glyph glyph);
		virtual ~FTVectoriser();
		
		bool Ingest();
		void Output( double* d);
		int points();
		int contours() const { return contourList.size();}
		int contourSize( int c) const { return contourList[c]->size();}
		
		// attributes
		int contourFlag; 
		
	private:
		// methods
		int Conic( int index, int first, int last);
		int Cubic( int index, int first, int last);
		void deCasteljau( GLfloat t, int n);
		void evaluateCurve( int n);

		// attributes
		vector< FTContour*> contourList;
		float ctrlPtArray[4][2]; // Magic numbers
			
		FTContour* contour;

		FT_Outline ftOutline;
		
		 // Magic numbers -- #define MAX_DEG 4
		float bValues[4][4][2];	//3D array storing values
                                        	//of de Casteljau algorithm.


};


#endif	//	__FTVectoriser__
