#ifndef     __FTGlyphContainer__
#define     __FTGlyphContainer__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTGL.h"
#include "FTBBox.h"
#include "FTPoint.h"
#include "FTVector.h"

class FTFace;
class FTGlyph;

/**
 * FTGlyphContainer holds the post processed FTGlyph objects.
 *
 * @see FTGlyph
 */
class FTGL_EXPORT FTGlyphContainer
{
    public:
        /**
         * Constructor
         *
         * @param face      The Freetype face
         */
        FTGlyphContainer( FTFace* face);

        /**
         * Destructor
         */
        ~FTGlyphContainer();

        /**
         * Adds a glyph to this glyph list.
         *
         * @param glyph The FTGlyph to be inserted into the container
         * @param g     The glyphs index in the container.
         * @return          <code>true</code>
         */
        bool Add( FTGlyph* glyph, unsigned int g);

        /**
         * Get a glyph from the glyph list
         *
         * @param c The char code of the glyph NOT the glyph index      
         * @return  An FTGlyph or <code>null</code> is it hasn't been
         * loaded.
         */
        FTGlyph* Glyph( const unsigned int c) const;

        
        FTBBox BBox( const unsigned int index) const;
        
        /**
        * Returns the kerned advance width for a glyph.
        *
        * @param index  glyph index of the character
        * @param next   the next glyph in a string
        * @return       advance width
        */
        float Advance( unsigned int index, unsigned int next);
        
        /**
         * Renders a character
         * @param index the glyph to be Rendered
         * @param next  the next glyph in the string. Used for kerning.
         * @param pen   the position to Render the glyph
         * @return      The distance to advance the pen position after Rendering
         */
        FTPoint Render( unsigned int index, unsigned int next, FTPoint pen);
        
        /**
         * Queries the Font for errors.
         *
         * @return  The current error code.
         */
        FT_Error Error() const { return err;}

    private:
        /**
         * How many glyphs are reserved in this container
         */
        unsigned int numberOfGlyphs;

        /**
         * The current FTGL face
         */
        FTFace* face;

        /**
         * A structure to hold the glyphs
         */
        typedef FTVector<FTGlyph*> GlyphVector;
        GlyphVector glyphs;

        /**
         * Current error code. Zero means no error.
         */
        FT_Error err;
        
};


#endif  //  __FTGlyphContainer__
