#include "LayoutEngine.h"
#include "FTLayoutFont.h"

FTLayoutFont::FTLayoutFont( const char* fontname, int script)
:   face( fontname)
{
    err = face.Error();
    LEErrorCode success;
    
    layoutEngine = LayoutEngine::layoutEngineFactory( &face,
                                                      (le_int32) script,
                                                      0,
                                                      (LEErrorCode &) success);

}
        
        
