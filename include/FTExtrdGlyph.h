#ifndef		__FTExtrdGlyph__
#define		__FTExtrdGlyph__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTGL.h"
#include "FTGlyph.h"

class FTVectoriser;

/**
 * FTPolyGlyph is a specialisation of FTGlyph for creating tessellated
 * polygon glyphs.
 * 
 * @see FTGlyphContainer
 * @see FTVectoriser
 *
 */
class FTGL_EXPORT FTExtrdGlyph : public FTGlyph
{
	public:
		/**
		 * Constructor
		 *
		 * @param glyph	The Freetype glyph to be processed
		 */
		FTExtrdGlyph( FT_Glyph glyph, float depth);

		/**
		 * Destructor
		 */
		virtual ~FTExtrdGlyph();

		/**
		 * Renders this glyph at the current pen position.
		 *
		 * @param pen	The current pen position.
		 * @return		The advance distance for this glyph.
		 */
		virtual float Render( const FT_Vector& pen);
		
	private:
		/**
		 * Calculate the winding direction of a contour.
		 *
		 * This uses the signed area of the contour. It is required because
		 * freetype doesn't do this despite the docs saying it does:(
		 */
		bool Winding( int numPoints, FTGL_DOUBLE *points);
		
		/**
		 * An object that helps convert freetype outlines into point
		 * data
		 */
		FTVectoriser* vectoriser;

		/**
		 * The total number of points in the Freetype outline
		 */
		int numPoints;

		/**
		 * Pointer to the point data
		 */
		FTGL_DOUBLE* frontMesh;
		FTGL_DOUBLE* backMesh;
		FTGL_DOUBLE* sidemesh;
		
		/**
		 * OpenGL display list
		 */
		GLuint glList;
		
		float depth;
	
};


#endif	//	__FTExtrdGlyph__

