#include "FTFace.h"
#include "LEFontInstance.h"


class FTICUFace : public LEFontInstance
{
    public:
        FTICUFace( const char* filename);

        FTICUFace( const unsigned char *pBufferBytes, size_t bufferSizeInBytes);
        
        ~FTICUFace();
        
        virtual const void *getFontTable(LETag tableTag) const;
        
        virtual le_bool canDisplay(LEUnicode32 ch) const;
        
        virtual le_int32 getUnitsPerEM() const;
        
        virtual void mapCharsToGlyphs(const LEUnicode chars[], le_int32 offset, le_int32 count, le_bool reverse, const LECharMapper *mapper, LEGlyphID glyphs[]) const;
        
        virtual LEGlyphID mapCharToGlyph(LEUnicode32 ch, const LECharMapper *mapper) const;
        
        virtual le_int32 getName(le_uint16 platformID, le_uint16 scriptID, le_uint16 languageID, le_uint16 nameID, LEUnicode *name) const;
        
        virtual void getGlyphAdvance(LEGlyphID glyph, LEPoint &advance) const;
        
        virtual le_bool getGlyphPoint(LEGlyphID glyph, le_int32 pointNumber, LEPoint &point) const;
        
        virtual float getXPixelsPerEm() const;
        
        virtual float getYPixelsPerEm() const;
        
        virtual float xUnitsToPoints(float xUnits) const;
        
        virtual float yUnitsToPoints(float yUunits) const;
        
        virtual void unitsToPoints(LEPoint &units, LEPoint &points) const;
        
        virtual float xPixelsToUnits(float xPixels) const;
        
        virtual float yPixelsToUnits(float yPixels) const;
        
        virtual void pixelsToUnits(LEPoint &pixels, LEPoint &units) const;
        
        virtual void transformFunits(float xFunits, float yFunits, LEPoint &pixels) const;
        
        FT_Error Error() const { return err;}

    private:
        FTFace face;
        FT_Error err;

};