#include <ft2build.h>
#include FT_FREETYPE_H

#include "FTICUFace.h"

namespace icu_2_4
{
    class LayoutEngine;
}

class FTLayoutFont
{
    public:
        FTLayoutFont( const char* fontname, int script);
        
        FT_Error Error() const { return err;}
        
    private:
        FTICUFace face;
        
        LayoutEngine* layoutEngine;
        
        FT_Error err;

};