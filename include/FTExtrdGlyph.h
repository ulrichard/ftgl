#ifndef		__FTExtrdGlyph__
#define		__FTExtrdGlyph__

#include "FTGL.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

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
		 * Convert the point data into a mesh.
		 *
		 * Uses GLUtesselator to create a mesh
		 */
		void Tesselate();
		
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
		double* frontMesh;
		double* backMesh;
		double* sidemesh;
		
		/**
		 * OpenGL display list
		 */
		GLuint glList;
		
		float depth;
	
};


#endif	//	__FTExtrdGlyph__

