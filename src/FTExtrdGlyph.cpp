#include	"FTExtrdGlyph.h"
#include	"FTVectoriser.h"


//#include "mmgr.h"

FTExtrdGlyph::FTExtrdGlyph( FT_Glyph glyph, float d)
:	FTGlyph(),
	vectoriser(0),
	numPoints(0),
	frontMesh(0),
	backMesh(0),
	sidemesh(0),
	glList(0),
	depth(d)
{
	if( ft_glyph_format_outline != glyph->format)
	{
		return;
	}

	vectoriser = new FTVectoriser( glyph);
	
	vectoriser->Process();

	// Make the front polygons
	vectoriser->MakeMesh( 1.0);
	
	numPoints = vectoriser->MeshPoints();
	if ( numPoints < 3)
	{
		delete vectoriser;
		return;
	}
	
	frontMesh = new double[ numPoints * 3];
	vectoriser->GetMesh( frontMesh);
	
	// Make the back polygons
	vectoriser->MakeMesh( -1.0);
	
	numPoints = vectoriser->MeshPoints();
	if ( numPoints < 3)
	{
		delete vectoriser;
		delete [] frontMesh;
		return;
	}
	
	backMesh =  new double[ numPoints * 3];
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
	
	// Build the edge polygons
	int* contourLength = new int[ numContours];
	for( int cn = 0; cn < numContours; ++cn)
	{
		contourLength[cn] = vectoriser->contourSize( cn);
	}
	
	sidemesh = new double[ numPoints * 3];
	vectoriser->GetOutline( sidemesh);
	
	delete vectoriser;
	
	// Draw the glyph
	int offset = 0;
	glList = glGenLists(1);
	glNewList( glList, GL_COMPILE);
		// Render Front Mesh
		int BEPairs = static_cast<int>(frontMesh[0]);
		for( int i = 0; i < BEPairs; ++i)
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
		for( int i = 0; i < BEPairs; ++i)
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
		
		FT_OutlineGlyph outline = (FT_OutlineGlyph)glyph;
		FT_Outline ftOutline = outline->outline;
		int contourFlag = ftOutline.flags;
		
		// Join them together.
		// Extrude each contour to make the sides.
		double* contour = sidemesh;
		for (int c=0; c<numContours; ++c)
		{
		
			// Make a quad strip using each successive
			// pair of points in this contour.
			int numPoints = contourLength[c];
			glBegin(GL_QUAD_STRIP);

				for (int j= 0; j <= numPoints; ++j)
				{
					int j1 = (j < numPoints) ? j : 0;
					int j0 = (j1 == 0) ? (numPoints-1) : (j1-1);

					double* p0 = contour + j0*3;
					double* p1 = contour + j1*3;

					// Compute normal for this quad.
					double vx = p1[0] - p0[0];
					double vy = p1[1] - p0[1];
					// Normalise
					double length = sqrt( ( ( vx * vx) + ( vy * vy)));
					vx /= length; vy /= length;
					glNormal3d(-vy, vx, 0.0);
					
					// Add vertices to the quad strip.
					// Winding order!!!
					if( contourFlag & ft_outline_reverse_fill)
					{
						glVertex3d(p0[0], p0[1], 0);
						glVertex3d(p0[0], p0[1], -depth);
					}
					else
					{
						glVertex3d(p0[0], p0[1], -depth);
						glVertex3d(p0[0], p0[1], 0);
					}
				} // for
			glEnd();
			contour += numPoints*3;
		} // for 
		
		
	glEndList();

	delete [] sidemesh; // FIXME
	delete [] frontMesh;
	delete [] backMesh;
	delete [] contourLength;

	bBox = FTBBox( glyph);
	bBox.z2 = -depth;
	advance = glyph->advance.x >> 16;
	
	// discard glyph image (bitmap or not)
	FT_Done_Glyph( glyph); // Why does this have to be HERE
}


FTExtrdGlyph::~FTExtrdGlyph()
{
//	if( data)
//		delete [] data; // FIXME
}


float FTExtrdGlyph::Render( const FT_Vector& pen)
{
	if( glList)
	{
		glTranslatef( pen.x, pen.y, 0);
			glCallList( glList);	
		glTranslatef( -pen.x, -pen.y, 0);
	}
	
	return advance;
}
