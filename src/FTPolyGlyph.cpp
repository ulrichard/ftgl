#include "FTPolyGlyph.h"
#include "FTVectoriser.h"


FTPolyGlyph::FTPolyGlyph( FT_Glyph glyph)
:   FTGlyph( glyph),
    glList(0)
{
    if( ft_glyph_format_outline != glyph->format)
    {
        return;
    }

    FTVectoriser* vectoriser = new FTVectoriser( glyph);

    vectoriser->MakeMesh(1.0);
    unsigned int numPoints = vectoriser->MeshPoints();

    if( numPoints < 3)
    {
        delete vectoriser;
        return;
    }
    
    FTGL_DOUBLE* data = new FTGL_DOUBLE[ numPoints * 3];
    vectoriser->GetMesh( data);
    delete vectoriser;

    int d = 0;
    glList = glGenLists(1);
    glNewList( glList, GL_COMPILE);

        int BEPairs = static_cast<int>(data[0]);
        for( int i = 0; i < BEPairs; ++i)
        {
            int polyType = static_cast<int>(data[d + 1]);
            glBegin( polyType);

            int verts = static_cast<int>(data[d+2]);

            d += 3;
            for( int x = 0; x < verts; ++x)
            {
                glVertex3dv( data + d);
                d += 3;
            }
            glEnd();
        }
    glEndList();

    delete [] data; // FIXME
    data = 0;

    // discard glyph image (bitmap or not)
    FT_Done_Glyph( glyph); // Why does this have to be HERE
}


FTPolyGlyph::~FTPolyGlyph()
{}


float FTPolyGlyph::Render( const FTPoint& pen)
{
    if( glList)
    {
        glTranslatef(  pen.x,  pen.y, 0);
        glCallList( glList);    
        glTranslatef( -pen.x, -pen.y, 0);
    }
    
    return advance;
}
