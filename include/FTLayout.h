#ifndef    __FTLayout__
#define    __FTLayout__

#include "FTGL.h"
#include "FTPoint.h"
#include "FTFont.h"

/**
 * FTLayout is the interface for layout managers that render text.
 *
 * Specific layout manager classes are derived from this class. This class
 * is abstract and deriving classes must implement the protected
 * <code>Render</code> methods to render formatted text and 
 * <code>BBox</code> methods to determine the bounding box of output text.
 *
 * @see     FTFont
 */
class FTGL_EXPORT FTLayout {
    public:        
        /**
         * Get the bounding box for a formatted string.
         *
         * @param string    a char string
         * @param llx       lower left near x coord
         * @param lly       lower left near y coord
         * @param llz       lower left near z coord
         * @param urx       upper right far x coord
         * @param ury       upper right far y coord
         * @param urz       upper right far z coord
         */
        virtual void BBox(const char* String,float& llx,float& lly,float& llz,float& urx,float& ury,float& urz) = 0;

        /**
         * Get the bounding box for a formatted string.
         *
         * @param string    a wchar_t string
         * @param llx       lower left near x coord
         * @param lly       lower left near y coord
         * @param llz       lower left near z coord
         * @param urx       upper right far x coord
         * @param ury       upper right far y coord
         * @param urz       upper right far z coord
         */
        virtual void BBox(const wchar_t* String,float& llx,float& lly,float& llz,float& urx,float& ury,float& urz) = 0;
            
        /**
         * Render a string of characters
         * 
         * @param string    'C' style string to be output.   
         */
        virtual void Render(const char *String) = 0;

        /**
         * Render a string of characters
         * 
         * @param string    wchar_t string to be output.     
         */
        virtual void Render(const wchar_t *String) = 0;
   protected:
        /**
         * Current pen or cursor position;
         */
        FTPoint pen;

        /**
         * Expose <code>FTFont::DoRender</code> method to derived classes.
         * 
         * @param font 		 The font that contains the glyph.
         * @param chr       current character
         * @param nextChr   next character
         * @see FTFont::DoRender
         */
        void DoRender(FTFont *font,const unsigned int chr,const unsigned int nextChr)
            { font->DoRender(chr,nextChr,pen); }
        
        /**
         * Expose <code>FTFont::CheckGlyph</code> method to derived classes.
         *
         * @param font The font that contains the glyph.
         * @param chr  character index
         */
        void CheckGlyph(FTFont *font,const unsigned int Chr)
            { font->CheckGlyph(Chr); }
            
         /**
          * Expose the FTFont <code>glyphList</code> to our derived classes.
          * 
          * @param font The font to perform the query on.
          * @param Char The character corresponding to the glyph to query.
          *
          * @return A pointer to the glyphList of font.
          */ 
         FTGlyphContainer *GetGlyphs(FTFont *font)
            { return(font->glyphList); }
            
         /** 
          * Expose the FTFont <code>charSize</code> to our derived classes.
          *
          * @param The font to perform the query on.
          *
          * @return A reference to the charSize object of font.
          */
         FTSize &GetCharSize(FTFont *font)
            { return(font->charSize); }
}; /* class FTLayout */
#endif  /* __FTLayout__ */

