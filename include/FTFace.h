#ifndef		__FTFace__
#define		__FTFace__

//#include "FTGL.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTSize.h"

/**
 * FTFace class provides an abstraction layer for the Freetype Face.
 *
 * @see	"Freetype 2 Documentation - 2.0.4"
 *
 */
class	FTFace
{
	public:
		// methods
		/**
		 * Default Constructor
		 */
		FTFace();

		/**
		 * Destructor
		 *
		 * Disposes of the current Freetype Face.
		 */
		virtual ~FTFace();

		/**
		 * Opens and reads a face file.
		 *
		 * @param fontname	font file name.
		 * @return			<code>true</code> if file has opened
		 *					successfully.
		 */
		bool Open( const char* filename);

		/**
		 * Disposes of the face
		 */
		void Close();
		

		/**
		 * Sets the char size for the current face.
		 *
		 * This doesn't guarantee that the size was set correctly. Clients
		 * should check errors.
		 *
		 * @params size		the face size in points (1/72 inch)
		 * @params res		the resolution of the target device.
		 * @return			<code>FTSize</code> object
		 */
		FTSize& Size( const unsigned int size, const unsigned int res);

		/**
		 * Sets the character map for the face.
		 *
		 * @params encoding		XXXXXXX
		 * @return				<code>true</code> if charmap was valid and
		 *						set correctly
		 */
		bool CharMap( FT_Encoding encoding);

		/**
		 *	Get the glyph index of the input character.
		 *
		 * @param
		 * @return
		 */
		unsigned int CharIndex( unsigned int index ) const;

		/**
		 * Gets the ferning vector between two glyphs
		 */
		FT_Vector& KernAdvance( unsigned int index1, unsigned int index2);
		

		/**
		 * Loads and creates a Freetype glyph.
		 */
		FT_Glyph& Glyph( unsigned int index, FT_Int load_flags);

		/**
		 * Gets the current Freetype face.
		 */
		FT_Face* Face() const { return ftFace;}
		

		/**
		 * Queries for errors.
		 *
		 * @return	The current error code.
		 */
		FT_Error Error() const { return err; }
		
		// attributes
		
	private:
		// methods
		
		// attributes

		/**
		 * The size object associated with this face
		 */
		FTSize	charSize;

		/**
		 * The Freetype face
		 */
		FT_Face* ftFace;

		/**
		 * Temporary variable to hold a glyph
		 */
		FT_Glyph ftGlyph;

		/**
		 * The number of character maps in this face.
		 */
		int	numCharMaps;

		/**
		 * The number of glyphs in this face
		 */
		int	numGlyphs;

		/**
		 * Temporary variable to holding a kerning vector.
		 */
		FT_Vector kernAdvance;
		
		/**
		 * Current error code. Zero means no error.
		 */
		FT_Error err;
};


#endif	//	__FTFace__
