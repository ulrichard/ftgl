#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

#include "FTVectoriser.h"


static const int RESOLUTION = 72;
static const int CHARACTER_SIZE = 72 * 64;

static const int NULL_CHARACTER_INDEX = ' ';
static const int SIMPLE_CHARACTER_INDEX = 'i';
static const int COMPLEX_CHARACTER_INDEX = 'd';

static const char* FONT_FILE = "../../test/arial.ttf";

static double testOutline[] = 
{
    29, 0, 0.0,
    29, 4.35938, 0.0,
    27.4194, 2.43, 0.0,
    25.565, 0.929375, 0.0,
    23.4369, -0.1425, 0.0,
    21.035, -0.785625, 0.0,
    18.3594, -1, 0.0,
    16.57, -0.901563, 0.0,
    14.8394, -0.60625, 0.0,
    13.1675, -0.114062, 0.0,
    11.5544, 0.575, 0.0,
    10, 1.46094, 0.0,
    8.54375, 2.52312, 0.0,
    7.225, 3.74094, 0.0,
    6.04375, 5.11437, 0.0,
    5, 6.64344, 0.0,
    4.09375, 8.32812, 0.0,
    3.34, 10.1438, 0.0,
    2.75375, 12.0656, 0.0,
    2.335, 14.0938, 0.0,
    2.08375, 16.2281, 0.0,
    2, 18.4688, 0.0,
    2.07563, 20.6588, 0.0,
    2.3025, 22.7662, 0.0,
    2.68063, 24.7913, 0.0,
    3.21, 26.7338, 0.0,
    3.89062, 28.5938, 0.0,
    4.72281, 30.3278, 0.0,
    5.70688, 31.8925, 0.0,
    6.84281, 33.2878, 0.0,
    8.13063, 34.5138, 0.0,
    9.57031, 35.5703, 0.0,
    11.1225, 36.445, 0.0,
    12.7478, 37.1253, 0.0,
    14.4462, 37.6112, 0.0,
    16.2178, 37.9028, 0.0,
    18.0625, 38, 0.0,
    19.4016, 37.9453, 0.0,
    20.6812, 37.7812, 0.0,
    21.9016, 37.5078, 0.0,
    23.0625, 37.125, 0.0,
    24.1641, 36.6328, 0.0,
    25.1962, 36.0538, 0.0,
    26.1491, 35.4103, 0.0,
    27.0225, 34.7025, 0.0,
    27.8166, 33.9303, 0.0,
    28.5312, 33.0938, 0.0,
    28.5312, 51, 0.0,
    35, 51, 0.0,
    35, 0, 0.0,
    9, 18.4844, 0.0,
    9.12031, 15.7244, 0.0,
    9.48125, 13.2569, 0.0,
    10.0828, 11.0819, 0.0,
    10.925, 9.19937, 0.0,
    12.0078, 7.60938, 0.0,
    13.2538, 6.31, 0.0,
    14.5853, 5.29938, 0.0,
    16.0025, 4.5775, 0.0,
    17.5053, 4.14438, 0.0,
    19.0938, 4, 0.0,
    20.6997, 4.1375, 0.0,
    22.205, 4.55, 0.0,
    23.6097, 5.2375, 0.0,
    24.9138, 6.2, 0.0,
    26.1172, 7.4375, 0.0,
    27.155, 8.95813, 0.0,
    27.9622, 10.77, 0.0,
    28.5388, 12.8731, 0.0,
    28.8847, 15.2675, 0.0,
    29, 17.9531, 0.0,
    28.8825, 20.8944, 0.0,
    28.53, 23.5056, 0.0,
    27.9425, 25.7869, 0.0,
    27.12, 27.7381, 0.0,
    26.0625, 29.3594, 0.0,
    24.8331, 30.67, 0.0,
    23.495, 31.6894, 0.0,
    22.0481, 32.4175, 0.0,
    20.4925, 32.8544, 0.0,
    18.8281, 33, 0.0,
    17.2025, 32.86, 0.0,
    15.6881, 32.44, 0.0,
    14.285, 31.74, 0.0,
    12.9931, 30.76, 0.0,
    11.8125, 29.5, 0.0,
    10.8, 27.9394, 0.0,
    10.0125, 26.0575, 0.0,
    9.45, 23.8544, 0.0,
    9.1125, 21.33, 0.0,
    9, 18.4844, 0.0
};


static GLenum testMeshPolygonTypes[] = 
{
    GL_TRIANGLE_FAN,
    GL_TRIANGLE_STRIP,
    GL_TRIANGLE_STRIP,
    GL_TRIANGLE_STRIP,
    GL_TRIANGLE_STRIP,
    GL_TRIANGLE_FAN, 
    GL_TRIANGLE_STRIP, 
    GL_TRIANGLE_FAN, 
    GL_TRIANGLE_FAN, 
    GL_TRIANGLE_FAN, 
    GL_TRIANGLE_STRIP, 
    GL_TRIANGLE_STRIP, 
    GL_TRIANGLE_STRIP, 
    GL_TRIANGLE_FAN
};


static unsigned int testMeshPointCount[] = 
{
    8, 7, 7, 9, 7, 6, 21, 5, 6, 6, 9, 13, 7, 7,
};


static double testMesh[] = 
{
    29, 4.35938, 0,
    29, 0, 0,
    35, 0, 0,
    29, 17.9531, 0,
    28.8847, 15.2675, 0,
    28.5388, 12.8731, 0,
    27.9622, 10.77, 0,
    27.4194, 2.43, 0,
    27.9622, 10.77, 0,
    27.155, 8.95813, 0,
    27.4194, 2.43, 0,
    26.1172, 7.4375, 0,
    25.565, 0.929375, 0,
    24.9137, 6.2, 0,
    23.6097, 5.2375, 0,
    25.565, 0.929375, 0,
    23.6097, 5.2375, 0,
    23.4369, -0.1425, 0,
    22.205, 4.55, 0,
    21.035, -0.785625, 0,
    20.6997, 4.1375, 0,
    19.0938, 4, 0,
    21.035, -0.785625, 0,
    19.0938, 4, 0,
    18.3594, -1, 0,
    17.5053, 4.14437, 0,
    16.57, -0.901563, 0,
    16.0025, 4.5775, 0,
    14.8394, -0.60625, 0,
    14.5853, 5.29938, 0,
    13.2537, 6.31, 0,
    14.8394, -0.60625, 0,
    13.2537, 6.31, 0,
    13.1675, -0.114062, 0,
    12.0078, 7.60938, 0,
    11.5544, 0.575, 0,
    10.925, 9.19938, 0,
    10.0828, 11.0819, 0,
    10, 1.46094, 0,
    11.5544, 0.575, 0,
    10.0828, 11.0819, 0,
    9.48125, 13.2569, 0,
    9.12031, 15.7244, 0,
    8.54375, 2.52312, 0,
    9.12031, 15.7244, 0,
    9, 18.4844, 0,
    8.54375, 2.52312, 0,
    8.13062, 34.5138, 0,
    7.225, 3.74094, 0,
    6.84281, 33.2878, 0,
    6.04375, 5.11438, 0,
    5.70688, 31.8925, 0,
    5, 6.64344, 0,
    4.72281, 30.3278, 0,
    4.09375, 8.32812, 0,
    3.89062, 28.5938, 0,
    3.34, 10.1438, 0,
    3.21, 26.7337, 0,
    2.75375, 12.0656, 0,
    2.68062, 24.7913, 0,
    2.335, 14.0938, 0,
    2.3025, 22.7663, 0,
    2.08375, 16.2281, 0,
    2.07562, 20.6588, 0,
    2, 18.4688, 0,
    35, 51, 0,
    28.5312, 51, 0,
    28.8825, 20.8944, 0,
    29, 17.9531, 0,
    35, 0, 0,
    28.5312, 33.0938, 0,
    27.8166, 33.9303, 0,
    27.9425, 25.7869, 0,
    28.53, 23.5056, 0,
    28.8825, 20.8944, 0,
    28.5312, 51, 0,
    27.12, 27.7381, 0,
    27.9425, 25.7869, 0,
    27.8166, 33.9303, 0,
    27.0225, 34.7025, 0,
    26.1491, 35.4103, 0,
    26.0625, 29.3594, 0,
    21.9016, 37.5078, 0,
    22.0481, 32.4175, 0,
    23.0625, 37.125, 0,
    23.495, 31.6894, 0,
    24.1641, 36.6328, 0,
    24.8331, 30.67, 0,
    25.1963, 36.0537, 0,
    26.0625, 29.3594, 0,
    26.1491, 35.4103, 0,
    12.9931, 30.76, 0,
    14.285, 31.74, 0,
    14.4462, 37.6113, 0,
    15.6881, 32.44, 0,
    16.2178, 37.9028, 0,
    17.2025, 32.86, 0,
    18.0625, 38, 0,
    18.8281, 33, 0,
    19.4016, 37.9453, 0,
    20.4925, 32.8544, 0,
    20.6813, 37.7812, 0,
    22.0481, 32.4175, 0,
    21.9016, 37.5078, 0,
    10.0125, 26.0575, 0,
    10.8, 27.9394, 0,
    11.1225, 36.445, 0,
    11.8125, 29.5, 0,
    12.7478, 37.1253, 0,
    12.9931, 30.76, 0,
    14.4462, 37.6113, 0,
    9.57031, 35.5703, 0,
    8.13062, 34.5138, 0,
    9, 18.4844, 0,
    9.1125, 21.33, 0,
    9.45, 23.8544, 0,
    10.0125, 26.0575, 0,
    11.1225, 36.445, 0
};


class FTVectoriserTest : public CppUnit::TestCase
{
        CPPUNIT_TEST_SUITE( FTVectoriserTest);
            CPPUNIT_TEST( testNullGlyphProcess);
            CPPUNIT_TEST( testBadGlyphProcess);
            CPPUNIT_TEST( testSimpleGlyphProcess);
            CPPUNIT_TEST( testComplexGlyphProcess);
            CPPUNIT_TEST( testGetOutline);
            CPPUNIT_TEST( testGetMesh);
        CPPUNIT_TEST_SUITE_END();
        
    public:
        FTVectoriserTest() : CppUnit::TestCase( "FTVectoriser Test")
        {}
        
        FTVectoriserTest( const std::string& name) : CppUnit::TestCase(name)
        {}

        void testNullGlyphProcess()
        {
            FTVectoriser vectoriser( NULL);
            CPPUNIT_ASSERT( vectoriser.ContourCount() == 0);
        }
        
        
        void testBadGlyphProcess()
        {
            setUpFreetype();
            loadGlyph( NULL_CHARACTER_INDEX);
            
            FTVectoriser vectoriser( glyph);
            CPPUNIT_ASSERT( vectoriser.ContourCount() == 0);
            
            tearDownFreetype();
        }
        

        void testSimpleGlyphProcess()
        {
            setUpFreetype();
            loadGlyph( SIMPLE_CHARACTER_INDEX);
            
            FTVectoriser vectoriser( glyph);

            CPPUNIT_ASSERT( vectoriser.ContourCount() == 2);
            CPPUNIT_ASSERT( vectoriser.PointCount() == 8);
            
            tearDownFreetype();
        }
        
        
        void testComplexGlyphProcess()
        {
            setUpFreetype();
            loadGlyph( COMPLEX_CHARACTER_INDEX);
            
            FTVectoriser vectoriser( glyph);

            CPPUNIT_ASSERT( vectoriser.ContourCount() == 2);
            CPPUNIT_ASSERT( vectoriser.PointCount() == 91);
            
            tearDownFreetype();
        }
        
        
        void testGetOutline()
        {
            setUpFreetype();
            loadGlyph( COMPLEX_CHARACTER_INDEX);
            
            FTVectoriser vectoriser( glyph);
            
            unsigned int d = 0;
            for( size_t c = 0; c < vectoriser.ContourCount(); ++c)
            {
                FTContour* contour = vectoriser.Contour(c);
                
                for( size_t p = 0; p < contour->PointCount(); ++p)
                {
                    CPPUNIT_ASSERT_DOUBLES_EQUAL( *(testOutline + d),     contour->Point(p).x / 64.0f, 0.01);
                    CPPUNIT_ASSERT_DOUBLES_EQUAL( *(testOutline + d + 1), contour->Point(p).y / 64.0f, 0.01);
                    d += 3;
                }
            }
            
            tearDownFreetype();
        }
        
        
        void testGetMesh()
        {
            setUpFreetype();
            loadGlyph( COMPLEX_CHARACTER_INDEX);
            
            FTVectoriser vectoriser( glyph);

            vectoriser.MakeMesh(1.0);

            int d = 0;
            FTMesh* mesh = vectoriser.GetMesh();
            unsigned int tesselations = mesh->TesselationCount();
            CPPUNIT_ASSERT( tesselations == 14);
            
            for( unsigned int index = 0; index < tesselations; ++index)
            {
                FTTesselation* subMesh = mesh->Tesselation( index);
                
                unsigned int polyType = subMesh->PolygonType();
                CPPUNIT_ASSERT( testMeshPolygonTypes[index] == polyType);
                
                unsigned int numberOfVertices = subMesh->PointCount();
                CPPUNIT_ASSERT( testMeshPointCount[index] == numberOfVertices);

                for( unsigned int x = 0; x < numberOfVertices; ++x)
                {
                    CPPUNIT_ASSERT_DOUBLES_EQUAL( *(testMesh + d),     subMesh->Point(x).x / 64, 0.01);
                    CPPUNIT_ASSERT_DOUBLES_EQUAL( *(testMesh + d + 1), subMesh->Point(x).y / 64, 0.01);
                    d += 3;
                }
            }

            tearDownFreetype();
        }
        
        
        void setUp() 
        {}
        
        
        void tearDown() 
        {}
        
    private:
        FT_Library   library;
        FT_Face      face;
        FT_Glyph     glyph;

        void setUpFreetype()
        {
            FT_Error error = FT_Init_FreeType( &library);
            assert(!error);
            error = FT_New_Face( library, FONT_FILE, 0, &face);
            assert(!error);
            
        }
        
        void loadGlyph( unsigned int characterIndex)
        {
            long glyphIndex = FT_Get_Char_Index( face, characterIndex);
            
            FT_Set_Char_Size( face, 0L, CHARACTER_SIZE, RESOLUTION, RESOLUTION);
            
            FT_Error error = FT_Load_Glyph( face, glyphIndex, FT_LOAD_DEFAULT);
            assert(!error);
            error = FT_Get_Glyph( face->glyph, &glyph);
            assert(!error);
        }
        
        void tearDownFreetype()
        {
            FT_Done_Glyph( glyph);
            FT_Done_Face( face);
            FT_Done_FreeType( library);
        }
        
};

CPPUNIT_TEST_SUITE_REGISTRATION( FTVectoriserTest);

