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
    if ( ( vectoriser->ContourCount() < 1) || ( vectoriser->PointCount() < 3))
    {
        delete vectoriser;
        return;
    }

    glList = glGenLists(1);
    glNewList( glList, GL_COMPILE);

        vectoriser->MakeMesh( 1.0);
        glNormal3d(0.0, 0.0, 1.0);
        
        const FTMesh* mesh = vectoriser->GetMesh();
        for( unsigned int index = 0; index < mesh->TesselationCount(); ++index)
        {
            const FTTesselation* subMesh = mesh->Tesselation( index);
            unsigned int polyonType = subMesh->PolygonType();

            glBegin( polyonType);
                for( unsigned int x = 0; x < subMesh->PointCount(); ++x)
                {
                    glVertex3f( subMesh->Point(x).x / 64.0f,
                                subMesh->Point(x).y / 64.0f,
                                0.0f);
                }
            glEnd();
        }
        
        vectoriser->MakeMesh( -1.0);
        glNormal3d(0.0, 0.0, -1.0);
        
        mesh = vectoriser->GetMesh();
        for( unsigned int index = 0; index < mesh->TesselationCount(); ++index)
        {
            const FTTesselation* subMesh = mesh->Tesselation( index);
            unsigned int polyonType = subMesh->PolygonType();

            glBegin( polyonType);
                for( unsigned int x = 0; x < subMesh->PointCount(); ++x)
                {
                    glVertex3f( subMesh->Point(x).x / 64.0f,
                                subMesh->Point(x).y / 64.0f,
                                -depth);
                }
            glEnd();
        }
        
        int contourFlag = vectoriser->ContourFlag();
        
        for( size_t c = 0; c < vectoriser->ContourCount(); ++c)
        {
            const FTContour* contour = vectoriser->Contour(c);
            unsigned int numberOfPoints = contour->PointCount();
            
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
                }
            glEnd();
        }
        
    glEndList();

    delete vectoriser;

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

