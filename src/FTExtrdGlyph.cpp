#include    <math.h>

#include    "FTExtrdGlyph.h"
#include    "FTVectoriser.h"


FTExtrdGlyph::FTExtrdGlyph( FT_Glyph glyph, float d)
:   FTGlyph( glyph),
    glList(0),
    depth(d)
{
    if( ft_glyph_format_outline != glyph->format)
    {
        return;
    }

    bBox.upperZ = -depth;
    
    FTVectoriser* vectoriser = new FTVectoriser( glyph);

    vectoriser->MakeMesh( 1.0);
    
    unsigned int numPoints = vectoriser->MeshPoints();
    if ( numPoints < 3)
    {
        delete vectoriser;
        return;
    }
    
    FTGL_DOUBLE* frontMesh = new FTGL_DOUBLE[ numPoints * 3];
    vectoriser->GetMesh( frontMesh);

    vectoriser->MakeMesh( -1.0);
    
    numPoints = vectoriser->MeshPoints();
    if ( numPoints < 3)
    {
        delete vectoriser;
        delete [] frontMesh;
        return;
    }
    
    FTGL_DOUBLE* backMesh =  new FTGL_DOUBLE[ numPoints * 3];
    vectoriser->GetMesh( backMesh);
    
    numPoints = vectoriser->points();
    int numContours = vectoriser->contours(); // FIXME
    
    if ( ( numContours < 1) || ( numPoints < 3))
    {
        delete vectoriser;
        delete [] frontMesh;
        delete [] backMesh;
        return;
    }
    
    // Draw the glyph
    int offset = 0;
    glList = glGenLists(1);
    glNewList( glList, GL_COMPILE);
    // Render Front Mesh
        int i;
        int BEPairs = static_cast<int>(frontMesh[0]);
        for( i = 0; i < BEPairs; ++i)
        {
            int polyType = (int)frontMesh[offset + 1];
            glBegin( polyType);
                glNormal3d(0.0, 0.0, 1.0);
        
                int verts = (int)frontMesh[offset+2];
                offset += 3;
                for( int x = 0; x < verts; ++x)
                {
                    glVertex3dv( frontMesh + offset);
                    offset += 3;
                }
            glEnd();
        }
        
    // Render Back Mesh
        offset = 0;
        BEPairs = static_cast<int>(backMesh[0]);
        for( i = 0; i < BEPairs; ++i)
        {
            int polyType = (int)backMesh[offset + 1];
            glBegin( polyType);

                glNormal3d(0.0, 0.0, -1.0);
                int verts = (int)backMesh[offset+2];
                offset += 3;
                for( int x = 0; x < verts; ++x)
                {
                    glVertex3d( backMesh[offset], backMesh[offset + 1], -depth); // FIXME
                    offset += 3;
                }
            glEnd();
        }
        
        int contourFlag = vectoriser->ContourFlag();
        
        for( unsigned int c = 0; c < vectoriser->contours(); ++c)
        {
            FTContour* contour = vectoriser->Contour(c);
            unsigned int numberOfPoints = contour->Points();
            
            glBegin( GL_QUAD_STRIP);
                for( unsigned int j = 0; j <= numberOfPoints; ++j)
                {
                    unsigned int index = ( j == numberOfPoints) ? 0 : j;
                    unsigned int nextIndex = ( index == numberOfPoints - 1) ? 0 : index + 1;
                    
                    FTPoint normal = GetNormal( contour->Point(index), contour->Point(nextIndex));
                    glNormal3f( normal.x, normal.y, 0.0f);
                    
                    if( contourFlag & ft_outline_reverse_fill)
                    {
                        glVertex3f( contour->Point(index).x / 64.0f, contour->Point(index).y / 64.0f, 0.0f);
                        glVertex3f( contour->Point(index).x / 64.0f, contour->Point(index).y / 64.0f, -depth);
                    }
                    else
                    {
                        glVertex3f( contour->Point(index).x / 64.0f, contour->Point(index).y / 64.0f, -depth);
                        glVertex3f( contour->Point(index).x / 64.0f, contour->Point(index).y / 64.0f, 0.0f);
                    }
                } // for
            glEnd();
        } // for 
        
    glEndList();

    delete vectoriser;
    
    delete [] frontMesh;
    delete [] backMesh;

    // discard glyph image (bitmap or not)
    FT_Done_Glyph( glyph); // Why does this have to be HERE
}


FTExtrdGlyph::~FTExtrdGlyph()
{}


float FTExtrdGlyph::Render( const FTPoint& pen)
{
    if( glList)
    {
        glTranslatef( pen.x, pen.y, 0);
            glCallList( glList);    
        glTranslatef( -pen.x, -pen.y, 0);
    }
    
    return advance;
}


FTPoint FTExtrdGlyph::GetNormal( const FTPoint &a, const FTPoint &b)
{
    float vectorX = a.x - b.x;
    float vectorY = a.y - b.y;
                              
    float length = sqrt( vectorX * vectorX + vectorY * vectorY );
    
    if( length > 0.0f)
    {
        length = 1 / length;
    }
    else
    {
        length = 0.0f;
    }
    
    return FTPoint( -vectorY * length,
                     vectorX * length,
                     0.0f);
}

