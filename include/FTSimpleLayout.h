#ifndef    __FTSimpleLayout__
#define    __FTSimpleLayout__

#include "FTLayout.h"
#include "FTBBox.h"

class FTFont;

class FTGL_EXPORT FTSimpleLayout : public FTLayout {
    public:        
        /**
         * Initializes line spacing to 1.0, alignment to 
         * ALIGN_LEFT and wrap to 100.0
         */
        FTSimpleLayout();
        
        /**
         * Get the bounding box for a string.
         *
         * @param string    a char string
         * @param llx       lower left near x coord
         * @param lly       lower left near y coord
         * @param llz       lower left near z coord
         * @param urx       upper right far x coord
         * @param ury       upper right far y coord
         * @param urz       upper right far z coord
         */
        virtual void BBox( const char* string, float& llx, float& lly, float& llz, float& urx, float& ury, float& urz);
        
        /**
         * Get the bounding box for a string.
         *
         * @param string    a wchar_t string
         * @param llx       lower left near x coord
         * @param lly       lower left near y coord
         * @param llz       lower left near z coord
         * @param urx       upper right far x coord
         * @param ury       upper right far y coord
         * @param urz       upper right far z coord
         */
        virtual void BBox( const wchar_t* string, float& llx, float& lly, float& llz, float& urx, float& ury, float& urz);
                        
        /**
         * Render a string of characters
         * 
         * @param string    'C' style string to be output.   
         */
        virtual void Render( const char* string );

        /**
         * Render a string of characters
         * 
         * @param string    wchar_t string to be output.     
         */
        virtual void Render( const wchar_t* string );
        
        /**
         * Render a string of characters and distribute extra space amongst
         * the whitespace regions of the string.
         *
         * @param String		'C' style string to output.
         * @param ExtraSpace  The amount of extra space to add to each run of 
         *                    whitespace.
         */
        void RenderSpace(const char *String,const float ExtraSpace = 0.0)
            { pen.X(0); pen.Y(0); RenderSpace(String, 0, -1, ExtraSpace); }

        /**
         * Render a string of characters and distribute extra space amongst
         * the whitespace regions of the string.
         *
         * @param String		wchar_t string to output.
         * @param ExtraSpace  The amount of extra space to add to each run of 
         *                    whitespace.
         */
        void RenderSpace(const wchar_t *String,const float ExtraSpace = 0.0)
            { pen.X(0); pen.Y(0); RenderSpace(String, 0, -1, ExtraSpace); }

        typedef enum {ALIGN_LEFT,ALIGN_CENTER,ALIGN_RIGHT,ALIGN_JUST} TextAlignment;
        
        /**
         * Set he font to use for rendering the text.  
         *
         * @param fontInit A pointer to the new font.  The font is
         *                 referenced by this but will not be 
         *                 disposed of when this is deleted.
         */
        void SetFont(FTFont *fontInit) 
            { currentFont = fontInit; }
        /**
         * @return The current font.
         */
        FTFont *GetFont() 
            { return(currentFont); }
        /**
         * The maximum line length for formatting text.
         *
         * @param LineLength The new line length.
         */
        void SetLineLength(const float LineLength)
            { lineLength = LineLength; }
            
        /**
         * @return The current line length.
         */
        float GetLineLength() const
            { return(lineLength); }
            
        /**
         * The text alignment mode used to distribute
         * space within a line or rendered text.
         *
         * @param Alignment The new alignment mode.
         */
        void SetAlignment(const TextAlignment Alignment) 
            { alignment = Alignment; }
        /**
         * @return The text alignment mode.
         */
        TextAlignment GetAlignment() const
            { return(alignment); }
            
        /**
         * Sets the line height.
         *
         * @param LineSpacing The height of each line of text expressed as
         *                    a percentage of the current fonts line height.
         */
        void SetLineSpacing(const float LineSpacing) 
            { lineSpacing = LineSpacing; }
            
        /**
         * @return The line spacing.
         */
        float GetLineSpacing() const
            { return(lineSpacing); }
   protected:
        /**
         * Render a string of characters and distribute extra space amongst
         * the whitespace regions of the string.  Note that this method
         * does not reset the pen position before rendering.  This method
         * provides the impelmentation for other RenderSpace methods and
         * thus should be overloaded when attempting to overload any
         * RenderSpace methods.
         *
         * @param String	A buffer of wchar_t characters to output.
         * @param Start    The index of the first character in String to output.
         * @param Stop     The index of the last character in String to output.
         * @param ExtraSpace The amount of extra space to distribute amongst
         *                   the characters.
         */
        virtual void RenderSpace(const char *String,const int Start,const int Stop,const float ExtraSpace = 0.0);

        /**
         * Render a string of characters and distribute extra space amongst
         * the whitespace regions of the string.  Note that this method
         * does not reset the pen position before rendering.  This method
         * provides the impelmentation for other RenderSpace methods and
         * thus should be overloaded when attempting to overload any
         * RenderSpace methods.
         *
         * @param String	A buffer of wchar_t characters to output.
         * @param Start    The index of the first character in String to output.
         * @param Stop     The index of the last character in String to output.
         * @param ExtraSpace The amount of extra space to distribute amongst
         *                   the characters.
         */
        virtual void RenderSpace(const wchar_t *String,const int Start,const int Stop,const float ExtraSpace = 0.0);
    private:        
        /**
         * Either render a string of characters and wrap lines
         * longer than a threshold or compute the bounds
         * of a string of characters when wrapped.  The functionality
         * of this method is exposed by the BBoxWrapped and
         * RenderWrapped methods.
         *
         * @param Buffer 		wchar_t style string to output.
         * @param bounds      A pointer to a bounds object.  If non null
         *                    the bounds of the text when laid out
         *                    will be stored in bounds.  If null the
         *                    text will be rendered.
         */      
        virtual void WrapText(const char *Buffer,FTBBox *bounds = NULL);
        
        /**
         * Either render a string of characters and wrap lines
         * longer than a threshold or compute the bounds
         * of a string of characters when wrapped.  The functionality
         * of this method is exposed by the BBoxWrapped and
         * RenderWrapped methods.
         *
         * @param Buffer 		wchar_t style string to output.
         * @param bounds      A pointer to a bounds object.  If non null
         *                    the bounds of the text when laid out
         *                    will be stored in bounds.  If null the
         *                    text will be rendered.
         */        
        virtual void WrapText(const wchar_t *Buffer,FTBBox *bounds = NULL);

        /**
         * A helper method used by WrapText to either output the text or
         * compute it's bounds.
         *
         * @param Buffer   A pointer to an array of character data.
         * @param StartIdx The index of the first character to process.
         * @param EndIdx   The index of the last character to process.  If 
         *                 < 0 then characters will be parsed until a '\0'
         *                 is encountered.
         * @param RemainingWidth The amount of extra space left on the line.
         * @param bounds     A pointer to a bounds object.  If non null the
         *                   bounds will be initialized or expanded by the 
         *                   bounds of the line.  If null the text will be 
         *                   rendered.  If the bounds are invalid (lower > upper)
         *                   they will be initialized.  Otherwise they
         *                   will be expanded.
         */
        void OutputWrapped(const char *Buffer,const int StartIdx,const int EndIdx,const float RemainingWidth,FTBBox *bounds);

        /**
         * A helper method used by WrapText to either output the text or
         * compute it's bounds.
         *
         * @param Buffer   A pointer to an array of character data.
         * @param StartIdx The index of the first character to process.
         * @param EndIdx   The index of the last character to process.  If 
         *                 < 0 then characters will be parsed until a '\0'
         *                 is encountered.
         * @param RemainingWidth The amount of extra space left on the line.
         * @param bounds     A pointer to a bounds object.  If non null the
         *                   bounds will be initialized or expanded by the 
         *                   bounds of the line.  If null the text will be 
         *                   rendered.  If the bounds are invalid (lower > upper)
         *                   they will be initialized.  Otherwise they
         *                   will be expanded.
         */
        void OutputWrapped(const wchar_t *Buffer,const int StartIdx,const int EndIdx,const float RemainingWidth,FTBBox *bounds);
        
        /**
         * The font to use for rendering the text.  The font is
         * referenced by this but will not be disposed of when this
         * is deleted.
         */
        FTFont          *currentFont;
        /**
         * The maximum line length for formatting text.
         */
        float				lineLength;
        
        /**
         * The text alignment mode used to distribute
         * space within a line or rendered text.
         */
        TextAlignment 	alignment;
        
        /**
         * The height of each line of text expressed as
         * a percentage of the fonts line height.
         */
        float 				lineSpacing;
}; /* class FTSimpleLayout */
#endif  /* __FTSimpleLayout__ */

