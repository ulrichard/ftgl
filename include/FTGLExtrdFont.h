#ifndef		__FTGLExtrdFont__
#define		__FTGLExtrdFont__

#include "FTGL.h"

#include	"FTFont.h"

class FTGlyph;


/**
 * FTGLExtrdFont is a specialisation of the FTFont class for handling
 * extruded Polygon fonts
 *
 * @see		FTFont
 * @see		FTGLPolygonFont
 */
class FTGL_EXPORT FTGLExtrdFont : public FTFont
{
	public:
		/**
		 * Default Constructor
		 */
		FTGLExtrdFont();
		
		/**
		 * Destructor
		 */
		~FTGLExtrdFont();
		
		void Depth( float d) { depth = d;}
		
	private:
		/**
		 * Construct a FTPolyGlyph.
		 *
		 * @param g The glyph index NOT the char code.
		 * @return	An FTExtrdGlyph or <code>null</code> on failure.
		 */
		inline virtual FTGlyph* MakeGlyph( unsigned int g);
		
		float depth;
		
};


#endif	//	__FTGLExtrdFont__

