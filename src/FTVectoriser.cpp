#include    "FTVectoriser.h"
#include    "FTGL.h"


#ifndef CALLBACK
#define CALLBACK
#endif

#ifdef __APPLE_CC__    
    typedef GLvoid (*GLUTesselatorFunction)(...);
#elif defined( __mips ) || defined( __linux__ )
    typedef GLvoid (*GLUTesselatorFunction)();
#elif defined ( WIN32)
    typedef GLvoid (CALLBACK *GLUTesselatorFunction)( );
#else
    #error "Error - need to define type GLUTesselatorFunction for this platform/compiler"
#endif
    

void CALLBACK ftglError( GLenum errCode, FTMesh* mesh)
{
    mesh->Error( errCode);
}

void CALLBACK ftglVertex( void* data, FTMesh* mesh)
{
    FTGL_DOUBLE* vertex = (FTGL_DOUBLE*)data;
    mesh->AddPoint( vertex[0], vertex[1], vertex[2]);
}


void CALLBACK ftglBegin( GLenum type, FTMesh* mesh)
{
    mesh->Begin( type);
}


void CALLBACK ftglEnd( FTMesh* mesh)
{
    mesh->End();
}


void CALLBACK ftglCombine( FTGL_DOUBLE coords[3], void* vertex_data[4], GLfloat weight[4], void** outData, FTMesh* mesh)
{
    FTGL_DOUBLE* vertex = (FTGL_DOUBLE*)coords;
    mesh->tempPointList.push_back( FTPoint( vertex[0], vertex[1], vertex[2]));
    
    *outData = &mesh->tempPointList[ mesh->tempPointList.size() - 1].x;
}
        

FTMesh::FTMesh()
:   err(0)
{
    tesselationList.reserve( 16);
    tempPointList.reserve( 128);
}


FTMesh::~FTMesh()
{
    for( size_t t = 0; t < tesselationList.size(); ++t)
    {
        delete tesselationList[t];
    }
    tesselationList.clear();

    tempPointList.clear();
}


void FTMesh::AddPoint( const FTGL_DOUBLE x, const FTGL_DOUBLE y, const FTGL_DOUBLE z)
{
    currentTesselation->AddPoint( x, y, z);
}

void FTMesh::Begin( GLenum m)
{
    currentTesselation = new FTTesselation;
    currentTesselation->meshType = m;
}


void FTMesh::End()
{
    tesselationList.push_back( currentTesselation);
}


int FTMesh::size() const
{
    int s = 0;
    for( size_t t = 0; t < tesselationList.size(); ++t)
    {
        s += tesselationList[t]->size();
// FIXME What the hell is this for? Data in FTPolyglyph
        ++s;
    }
    return s;
}


FTVectoriser::FTVectoriser( const FT_Glyph glyph)
:   mesh(0),
    ftContourCount(0),
    contourFlag(0),
    kBSTEPSIZE( 0.2f)
{
    if( glyph)
    {
        FT_OutlineGlyph outline = (FT_OutlineGlyph)glyph;
        ftOutline = outline->outline;
        
        ftContourCount = ftOutline.n_contours;;
        contourList = 0;
        contourFlag = ftOutline.flags;
    }
}


FTVectoriser::~FTVectoriser()
{
    for( size_t c = 0; c < contours(); ++c)
    {
        delete contourList[c];
    }

    delete [] contourList;
    
    if( mesh)
        delete mesh;
}


void FTVectoriser::ProcessContours()
{
    short contourLength = 0;
    short startIndex = 0;
    short endIndex = 0;
    
    contourList = new (FTContour*)[ftContourCount];
    
    for( short contourIndex = 0; contourIndex < ftContourCount; ++contourIndex)
    {
        FT_Vector* pointList = &ftOutline.points[startIndex];
        char* tagList = &ftOutline.tags[startIndex];
        
        endIndex = ftOutline.contours[contourIndex];
        contourLength =  ( endIndex - startIndex) + 1;

        FTContour* contour = new FTContour( pointList, tagList, contourLength);
        
        contourList[contourIndex] = contour;
        
        startIndex = endIndex + 1;
    }
}


int FTVectoriser::points()
{
    int s = 0;
    for( size_t c = 0; c < contours(); ++c)
    {
        s += contourList[c]->size();
    }
    
    return s;
}


void FTVectoriser::GetOutline( FTGL_DOUBLE* data)
{
    int i = 0;
    for( size_t c= 0; c < contours(); ++c)
    {
        const FTContour* contour = contourList[c];
        
        for( size_t p = 0; p < contour->size(); ++p)
        {
            data[i] = static_cast<FTGL_DOUBLE>(contour->pointList[p].x / 64.0f);
            data[i + 1] = static_cast<FTGL_DOUBLE>(contour->pointList[p].y / 64.0f);
            data[i + 2] = 0.0f;
            i += 3;
        }
    }
}


void FTVectoriser::MakeMesh( FTGL_DOUBLE zNormal)
{
    if( mesh)
    {
        delete mesh;
    }
        
    mesh = new FTMesh;
    
    GLUtesselator* tobj = gluNewTess();

    gluTessCallback( tobj, GLU_TESS_BEGIN_DATA,     (GLUTesselatorFunction)ftglBegin);
    gluTessCallback( tobj, GLU_TESS_VERTEX_DATA,    (GLUTesselatorFunction)ftglVertex);
    gluTessCallback( tobj, GLU_TESS_COMBINE_DATA,   (GLUTesselatorFunction)ftglCombine);
    gluTessCallback( tobj, GLU_TESS_END_DATA,       (GLUTesselatorFunction)ftglEnd);
    gluTessCallback( tobj, GLU_TESS_ERROR_DATA,     (GLUTesselatorFunction)ftglError);
    
    if( contourFlag & ft_outline_even_odd_fill) // ft_outline_reverse_fill
    {
        gluTessProperty( tobj, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_ODD);
    }
    else
    {
        gluTessProperty( tobj, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_NONZERO);
    }
    
    
    gluTessProperty( tobj, GLU_TESS_TOLERANCE, 0);
    gluTessNormal( tobj, 0.0f, 0.0f, zNormal);
    gluTessBeginPolygon( tobj, mesh);
    
        for( size_t c = 0; c < contours(); ++c)
        {
            const FTContour* contour = contourList[c];

            gluTessBeginContour( tobj);
            
                for( size_t p = 0; p < contour->size(); ++p)
                {
                    FTGL_DOUBLE* d = const_cast<FTGL_DOUBLE*>(&contour->pointList[p].x);
                    gluTessVertex( tobj, d, d);
                }

            gluTessEndContour( tobj);
        }
        
    gluTessEndPolygon( tobj);

    gluDeleteTess( tobj);
}


void FTVectoriser::GetMesh( FTGL_DOUBLE* data)
{
    // fill out the header
    size_t msize = mesh->tesselationList.size();
    data[0] = msize;
    
    int i = 0;
    for( int p = 0; p < data[0]; ++p)
    {
        FTTesselation* tesselation = mesh->tesselationList[p];
        size_t tesselationSize =  tesselation->pointList.size();
        int tesselationType =  tesselation->meshType;
        
        data[i+1] = tesselationType;
        data[i+2] = tesselationSize;

        i += 3;
        for( size_t q = 0; q < ( tesselation->pointList.size()); ++q)
        {
            data[i] = tesselation->pointList[q].x / 64.0f;
            data[i + 1] = tesselation->pointList[q].y / 64.0f;
            data[i + 2] = 0.0f;
            i += 3;
        }
    }
}

