#ifndef		__FTGlyph__
#define		__FTGlyph__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

//#include "FTGL.h"

/**
 * FTGlyph is the base clas for FTGL glyphs.
 *
 * It provides the interface between Freetype glyphs and their openGL
 * renderable counterparts. This is an abstract class and derived classes
 * must implement the <code>render</code> function. 
 * 
 * @see FTGlyphContainer
 *
 */
class FTGlyph
{
	public:
		// methods

		/**
		 * Constructor
		 *
		 * @param glyphIndex	The glyph index for this glyph
		 */
		FTGlyph( unsigned int glyphIndex);

		/**
		 * Destructor
		 */
		virtual ~FTGlyph();

		/**
		 * Renders this glyph at the current pen position.
		 *
		 * @param v		The current pen position.
		 * @return		The advance distance for this glyph.
		 */
		virtual float Render( const FT_Vector& v) = 0;

		/**
		 * Queries for errors.
		 *
		 * @return	The current error code.
		 */
		FT_Error Error() const { return err;}
		
		// attributes

		/**
		 * The glyph index
		 */
		const unsigned int glyphIndex; // FIXME make this private
		
	protected:
		// methods
		
		// attributes

		/**
		 * The advance distance for this glyph
		 */
		float advance;

		/**
		 * Vector from the pen position to the topleft corner of the glyph
		 */
		FT_Vector pos;

		/**
		 * Temporary holder for the Freetype glyph
		 */
		FT_Glyph ftGlyph;
		
		/**
		 * Current error code. Zero means no error.
		 */
		FT_Error err;
		
	private:
		// methods
		
		// attributes
		
};


#endif	//	__FTGlyph__
