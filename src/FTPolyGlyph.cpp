#include	"FTPolyGlyph.h"
#include	"FTVectoriser.h"


FTPolyGlyph::FTPolyGlyph( FT_Glyph glyph)
:	FTGlyph(),
	vectoriser(0),
	numPoints(0),
	data(0),
	glList(0)
{
	if( ft_glyph_format_outline != glyph->format)
	{ return;}

	vectoriser = new FTVectoriser( glyph);
	
	vectoriser->Process();

	vectoriser->MakeMesh();
	numPoints = vectoriser->MeshPoints();

	if ( numPoints < 3)
	{
		delete vectoriser;
		return;
	}
	
	data = new double[ numPoints * 3];

	vectoriser->GetMesh( data);
	
	advance = glyph->advance.x >> 16;

	delete vectoriser;
	
	glList = glGenLists(1);
	int d = 0;

	glNewList( glList, GL_COMPILE);
		int BEPairs = data[0];
		for( int i = 0; i < BEPairs; ++i)
		{
			int polyType = (int)data[d + 1];
			glBegin( polyType);

			int verts = (int)data[d+2];
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
{
//	if( data)
//		delete [] data; // FIXME
}


float FTPolyGlyph::Render( const FT_Vector& pen)
{
	if( glList)
	{
		glTranslatef( pen.x, pen.y, 0);
			glCallList( glList);	
		glTranslatef( -pen.x, -pen.y, 0);
	}
	
	return advance;
}
