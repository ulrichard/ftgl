#ifndef		__FTVectoriser__
#define		__FTVectoriser__

#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTGlyph.h"

class FTContour
{
	public:
		// methods
		FTContour();
		~FTContour();
	
		void AddPoint( int x, int y);
		
		int size() const { return pointList.size();}

		// attributes
		
		typedef pair<int, int> ftPoint;
		vector< ftPoint> pointList;
		float ctrlPtArray[4][2];
	private:
		// methods

		// attributes
};

//FIXME get rid of this
#define MAX_DEG 4

class FTVectoriser
{
	public:
		// methods
		FTVectoriser( FT_Glyph glyph);
		virtual ~FTVectoriser();
		
		bool Ingest();
		void Output( float* d);
		int points();
		int contours() const { return contourList.size();}
		int contourSize( int c) const { return contourList[c]->size();}
		
		// attributes
		
	private:
		// methods
		int Conic( int index, int first, int last);
		int Cubic( int index, int first, int last);
		void deCasteljau( GLfloat t, int n, GLfloat bValues[MAX_DEG][MAX_DEG][2]);
		void evaluateCurve( int n);

		// attributes
//		typedef pair<int, int> ftPoint;
//		vector< FT_Vector> pointList;
		vector< FTContour*> contourList;
		float ctrlPtArray[4][2];
			
		FTContour* contour;

		FT_Outline ftOutline;

};


#endif	//	__FTVectoriser__
