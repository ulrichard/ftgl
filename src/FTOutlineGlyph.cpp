#include    "FTOutlineGlyph.h"
#include    "FTVectoriser.h"


FTOutlineGlyph::FTOutlineGlyph( FT_Glyph glyph)
:   FTGlyph( glyph),
    glList(0)
{
    if( ft_glyph_format_outline != glyph->format)
    {
        return;
    }

    FTVectoriser* vectoriser = new FTVectoriser( glyph);
    
    vectoriser->ProcessContours();
    
    unsigned int numPoints = vectoriser->points();
    unsigned int numContours = vectoriser->contours();
    
    if ( ( numContours < 1) || ( numPoints < 3))
    {
        delete vectoriser;
        return;
    }
    
    FTGL_DOUBLE* data = new FTGL_DOUBLE[ numPoints * 3];
    vectoriser->GetOutline( data);
    
    int d = 0;
    glList = glGenLists(1);
    glNewList( glList, GL_COMPILE);
        for( unsigned int c = 0; c < numContours; ++c)
        {
            glBegin( GL_LINE_LOOP);
                int contourLength = vectoriser->contourSize( c);
                for( int p = 0; p < contourLength; ++p)
                {
                    glVertex2dv( data + d);
                    d += 3;
                }
            glEnd();
        }
    glEndList();

    delete vectoriser;
    delete [] data; // FIXME

    // discard glyph image (bitmap or not)
    FT_Done_Glyph( glyph); // Why does this have to be HERE
}


FTOutlineGlyph::~FTOutlineGlyph()
{}


float FTOutlineGlyph::Render( const FTPoint& pen)
{
    if( glList)
    {
        glTranslatef( pen.x, pen.y, 0);
            glCallList( glList);
        glTranslatef( -pen.x, -pen.y, 0);
    }
    
    return advance;
}

