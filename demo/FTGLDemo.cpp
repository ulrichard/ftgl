#ifdef __APPLE_CC__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tb.h"

#include "FTGLExtrdFont.h"
#include "FTGLOutlineFont.h"
#include "FTGLPolygonFont.h"
#include "FTGLTextureFont.h"
#include "FTGLPixmapFont.h"
#include "FTGLBitmapFont.h"
#include "FTSimpleLayout.h"

// YOU'LL PROBABLY WANT TO CHANGE THESE
#ifdef __linux__
	#define FONT_FILE "/usr/share/fonts/truetype/arial.ttf"
#endif
#ifdef __APPLE_CC__
	//#define FONT_FILE "/Users/henry/Development/PROJECTS/FTGL/ftglcvs/FTGL/test/arial.ttf"
   #define FONT_FILE "/Users/progers/Desktop/arial.ttf"
#endif
#ifdef WIN32
	#define FONT_FILE "C:\\WINNT\\Fonts\\arial.ttf"
#endif
#ifndef FONT_FILE
	#define FONT_FILE 0
#endif

#define EDITING 1
#define INTERACTIVE 2

#define FTGL_BITMAP 0
#define FTGL_PIXMAP 1
#define FTGL_OUTLINE 2
#define FTGL_POLYGON 3
#define FTGL_EXTRUDE 4
#define FTGL_TEXTURE 5

char* fontfile = FONT_FILE;
int current_font = FTGL_EXTRUDE;

GLint w_win = 640, h_win = 480;
int mode = INTERACTIVE;
int carat = 0;

FTSimpleLayout simpleLayout;
FTLayout			*layouts[] = { &simpleLayout, NULL};
int currentLayout = 0;
const int NumLayouts = 2;

const float InitialLineLength = 300.0f;

const float OX = -100;
const float OY = 200;

//wchar_t myString[16] = { 0x6FB3, 0x9580};
char myString[4096];

static FTFont* fonts[6];
static FTGLPixmapFont* infoFont;

void SetCamera(void);

void setUpLighting()
{
   // Set up lighting.
   float light1_ambient[4]  = { 1.0, 1.0, 1.0, 1.0 };
   float light1_diffuse[4]  = { 1.0, 0.9, 0.9, 1.0 };
   float light1_specular[4] = { 1.0, 0.7, 0.7, 1.0 };
   float light1_position[4] = { -1.0, 1.0, 1.0, 0.0 };
   glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_ambient);
   glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_diffuse);
   glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
   glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
   glEnable(GL_LIGHT1);

   float light2_ambient[4]  = { 0.2, 0.2, 0.2, 1.0 };
   float light2_diffuse[4]  = { 0.9, 0.9, 0.9, 1.0 };
   float light2_specular[4] = { 0.7, 0.7, 0.7, 1.0 };
   float light2_position[4] = { 1.0, -1.0, -1.0, 0.0 };
   glLightfv(GL_LIGHT2, GL_AMBIENT,  light2_ambient);
   glLightfv(GL_LIGHT2, GL_DIFFUSE,  light2_diffuse);
   glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
   glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
//   glEnable(GL_LIGHT2);

   float front_emission[4] = { 0.3, 0.2, 0.1, 0.0 };
   float front_ambient[4]  = { 0.2, 0.2, 0.2, 0.0 };
   float front_diffuse[4]  = { 0.95, 0.95, 0.8, 0.0 };
   float front_specular[4] = { 0.6, 0.6, 0.6, 0.0 };
   glMaterialfv(GL_FRONT, GL_EMISSION, front_emission);
   glMaterialfv(GL_FRONT, GL_AMBIENT, front_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, front_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, front_specular);
   glMaterialf(GL_FRONT, GL_SHININESS, 16.0);
   glColor4fv(front_diffuse);

   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
   glEnable(GL_CULL_FACE);
   glColorMaterial(GL_FRONT, GL_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);

   glEnable(GL_LIGHTING);
   glShadeModel(GL_SMOOTH);
}


void setUpFonts( const char* fontfile)
{
	fonts[FTGL_BITMAP] = new FTGLBitmapFont( fontfile);
	fonts[FTGL_PIXMAP] = new FTGLPixmapFont( fontfile);
	fonts[FTGL_OUTLINE] = new FTGLOutlineFont( fontfile);
	fonts[FTGL_POLYGON] = new FTGLPolygonFont( fontfile);
	fonts[FTGL_EXTRUDE] = new FTGLExtrdFont( fontfile);
	fonts[FTGL_TEXTURE] = new FTGLTextureFont( fontfile);

	for( int x = 0; x < 6; ++x)
	{
		if( fonts[x]->Error())
		{
			fprintf( stderr, "Failed to open font %s", fontfile);
			exit(1);
		}
		
		if( !fonts[x]->FaceSize( 24))
		{
			fprintf( stderr, "Failed to set size");
			exit(1);
		}
	
		fonts[x]->Depth(20);
		
		fonts[x]->CharMap(ft_encoding_unicode);
	}
	
	infoFont = new FTGLPixmapFont( fontfile);
	
	if( infoFont->Error())
	{
		fprintf( stderr, "Failed to open font %s", fontfile);
		exit(1);
	}
	
	infoFont->FaceSize( 18);

   strcpy(myString,"OpenGL is a powerful software interface for graphics hardware that allows graphics programmers to produce high-quality color images of 3D objects. abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
}


void renderFontmetrics()
{
	float x1, y1, z1, x2, y2, z2;
   if (layouts[currentLayout]) {
      layouts[currentLayout]->BBox(myString, x1, y1, z1, x2, y2, z2);
   } else {
      fonts[current_font]->BBox( myString, x1, y1, z1, x2, y2, z2);
   } /* If there is a layout use it to compute the bbox, otherwise query as a string (if/else layouts[]) */
  
	// Draw the bounding box
	glDisable( GL_LIGHTING);
	glDisable( GL_TEXTURE_2D);
			glEnable( GL_LINE_SMOOTH);
			glEnable(GL_BLEND);
			glBlendFunc( GL_SRC_ALPHA, GL_ONE); // GL_ONE_MINUS_SRC_ALPHA
   
	glColor3f( 0.0, 1.0, 0.0);
	// Draw the front face
	glBegin( GL_LINE_LOOP);
		glVertex3f( x1, y1, z1);
		glVertex3f( x1, y2, z1);
		glVertex3f( x2, y2, z1);
		glVertex3f( x2, y1, z1);
	glEnd();
	// Draw the back face
	if( current_font == FTGL_EXTRUDE && z1 != z2)
	{
		glBegin( GL_LINE_LOOP);
			glVertex3f( x1, y1, z2);
			glVertex3f( x1, y2, z2);
			glVertex3f( x2, y2, z2);
			glVertex3f( x2, y1, z2);
		glEnd();
	// Join the faces
		glBegin( GL_LINES);
			glVertex3f( x1, y1, z1);
			glVertex3f( x1, y1, z2);
			
			glVertex3f( x1, y2, z1);
			glVertex3f( x1, y2, z2);
			
			glVertex3f( x2, y2, z1);
			glVertex3f( x2, y2, z2);
			
			glVertex3f( x2, y1, z1);
			glVertex3f( x2, y1, z2);
		glEnd();
	}
	
   if (!layouts[currentLayout]) {
		/* There is no layout. Draw the baseline, Ascender and Descender */
      glBegin( GL_LINES);
         glColor3f( 0.0, 0.0, 1.0);
         glVertex3f( 0.0, 0.0, 0.0);
         glVertex3f( fonts[current_font]->Advance( myString), 0.0, 0.0);
         glVertex3f( 0.0, fonts[current_font]->Ascender(), 0.0);
         glVertex3f( 0.0, fonts[current_font]->Descender(), 0.0);
   } else if (layouts[currentLayout] && (dynamic_cast <FTSimpleLayout *>(layouts[currentLayout]))) {
      float lineWidth = ((FTSimpleLayout *)layouts[currentLayout])->GetLineLength();
      
      /* The layout is a simple layout.  Render guides that mark the edges of the wrap region */
      glColor3f(0.5,1.0,1.0);
      glBegin( GL_LINES);
         glVertex3f( 0, 10000, 0);
         glVertex3f( 0,-10000, 0);
         glVertex3f( lineWidth, 10000, 0);
         glVertex3f( lineWidth,-10000, 0);
      glEnd();
   } /* Render layout specific metrics (if/elseif layouts[currentLayout]) */
		
	glEnd();
	
	// Draw the origin
	glColor3f( 1.0, 0.0, 0.0);
	glPointSize( 5.0);
	glBegin( GL_POINTS);
		glVertex3f( 0.0, 0.0, 0.0);
	glEnd();
}


void renderFontInfo()
{
    glMatrixMode( GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w_win, 0, h_win);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// draw mode
	glColor3f( 1.0, 1.0, 1.0);
	glRasterPos2f( 20.0f , h_win - ( 20.0f + infoFont->Ascender()));

	switch( mode)
	{
		case EDITING:
			infoFont->Render("Edit Mode");
			break;
		case INTERACTIVE:
			break;
	}
	
	// draw font type
	glRasterPos2i( 20 , 20);
	switch( current_font)
	{
		case FTGL_BITMAP:
			infoFont->Render("Bitmap Font");
			break;
		case FTGL_PIXMAP:
			infoFont->Render("Pixmap Font");
			break;
		case FTGL_OUTLINE:
			infoFont->Render("Outline Font");
			break;
		case FTGL_POLYGON:
			infoFont->Render("Polygon Font");
			break;
		case FTGL_EXTRUDE:
			infoFont->Render("Extruded Font");
			break;
		case FTGL_TEXTURE:
			infoFont->Render("Texture Font");
			break;
	}
	
	glRasterPos2f( 20.0f , 20.0f + infoFont->Ascender() - infoFont->Descender());
	infoFont->Render(fontfile);
   
   if (layouts[currentLayout] && (dynamic_cast <FTSimpleLayout *>(layouts[currentLayout]))) { 
      glRasterPos2f( 20.0f , 20.0f + 2*(infoFont->Ascender() - infoFont->Descender()));
      switch (((FTSimpleLayout *)layouts[currentLayout])->GetAlignment()) {
         case FTSimpleLayout::ALIGN_LEFT: infoFont->Render("Align Left"); break;
         case FTSimpleLayout::ALIGN_RIGHT: infoFont->Render("Align Right"); break;
         case FTSimpleLayout::ALIGN_CENTER: infoFont->Render("Align Center"); break;
         case FTSimpleLayout::ALIGN_JUST: infoFont->Render("Align Justified"); break;
      } /* Output the alignment mode of the layout (switch GetAlignment()) */
   } /* If the current layout is a simple layout output the alignemnt mode (if layouts[currentLayout]) */
}

void do_display (void)
{
	switch( current_font)
	{
		case FTGL_BITMAP:
		case FTGL_PIXMAP:
		case FTGL_OUTLINE:
			break;
		case FTGL_POLYGON:
			glDisable( GL_BLEND);
			setUpLighting();
			break;
		case FTGL_EXTRUDE:
			glEnable( GL_DEPTH_TEST);
			glDisable( GL_BLEND);
			setUpLighting();
			break;
		case FTGL_TEXTURE:
			glEnable( GL_TEXTURE_2D);
			glDisable( GL_DEPTH_TEST);
			setUpLighting();
			glNormal3f( 0.0, 0.0, 1.0);
			break;

	}

	glColor3f( 1.0, 1.0, 1.0);
// If you do want to switch the color of bitmaps rendered with glBitmap,
// you will need to explicitly call glRasterPos3f (or its ilk) to lock
// in a changed current color.

   if (layouts[currentLayout]) {
      layouts[currentLayout]->Render(myString);
   } else {
      fonts[current_font]->Render( myString);
   } /* If there is an active layout use it to render the font (if/else layouts[currentLayout]) */
   
   renderFontmetrics();
   renderFontInfo();
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   	SetCamera();
	
	switch( current_font)
	{
		case FTGL_BITMAP:
		case FTGL_PIXMAP:
			glRasterPos2i((long)( w_win / 2 + OX),(long)( h_win / 2 + OY));
			glTranslatef(w_win / 2 + OX,h_win / 2 + OY, 0.0);
			break;
		case FTGL_OUTLINE:
		case FTGL_POLYGON:
		case FTGL_EXTRUDE:
		case FTGL_TEXTURE:
         glTranslatef(OX,OY,0);
			tbMatrix();
			break;
	}
	
	glPushMatrix();

	do_display();

	glPopMatrix();
	
    glutSwapBuffers();
}


void myinit( const char* fontfile)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor( 0.13, 0.17, 0.32, 0.0);
	glColor3f( 1.0, 1.0, 1.0);
	
	glEnable( GL_CULL_FACE);
	glFrontFace( GL_CCW);
	
	glEnable( GL_DEPTH_TEST);
	
	glEnable( GL_POLYGON_OFFSET_LINE);
	glPolygonOffset( 1.0, 1.0); // ????
	 	
	SetCamera();

	tbInit(GLUT_LEFT_BUTTON);
	tbAnimate( GL_FALSE);

   setUpFonts( fontfile);
    
   /* Configure the simple layout */
   simpleLayout.SetLineLength(InitialLineLength);
   simpleLayout.SetFont(fonts[current_font]);
}


void parsekey(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27: exit(0); break;
		case 13:
			if( mode == EDITING)
			{
				mode = INTERACTIVE;
			}
			else
			{
				mode = EDITING;
				carat = 0;
			}
			break;
      case '\t':
         if (layouts[currentLayout] && (dynamic_cast <FTSimpleLayout *>(layouts[currentLayout]))) {
            FTSimpleLayout *simpleLayout = (FTSimpleLayout *)layouts[currentLayout];
            switch (simpleLayout->GetAlignment()) {
               case FTSimpleLayout::ALIGN_LEFT: 	simpleLayout->SetAlignment(FTSimpleLayout::ALIGN_RIGHT); break;
               case FTSimpleLayout::ALIGN_RIGHT: 	simpleLayout->SetAlignment(FTSimpleLayout::ALIGN_CENTER); break;
               case FTSimpleLayout::ALIGN_CENTER:	simpleLayout->SetAlignment(FTSimpleLayout::ALIGN_JUST); break;
               case FTSimpleLayout::ALIGN_JUST: 	simpleLayout->SetAlignment(FTSimpleLayout::ALIGN_LEFT); break;
            } /* Decrement the layout (switch GetAlignemnt()) */
         } /* If the current layout is a simple layout change it's alignment properties (if simpleLayout) */
         break;
		default:
			if( mode == INTERACTIVE)
			{
				myString[0] = key;
				myString[1] = 0;
				break;
			}
			else
			{
				myString[carat] = key;
				myString[carat + 1] = 0;
				carat = carat > 2000 ? 2000 : ++carat;
			}
	}

	glutPostRedisplay();

}

void parseSpecialKey(int key, int x, int y)
{
   FTSimpleLayout *simpleLayout = NULL;
   if (layouts[currentLayout] && (dynamic_cast <FTSimpleLayout *>(layouts[currentLayout]))) {
      simpleLayout = (FTSimpleLayout *)layouts[currentLayout];
   } /* If the currentLayout is a simple layout store a pointer in simpleLayout (if layouts[currentLayout]) */

	switch (key)
	{
		case GLUT_KEY_UP:
			current_font = (current_font + 1)%5;
			break;
		case GLUT_KEY_DOWN:
			current_font = (current_font + 4)%5;
			break;
      case GLUT_KEY_PAGE_UP:
         currentLayout = (currentLayout + 1)%NumLayouts;
         break;
      case GLUT_KEY_PAGE_DOWN:
         currentLayout = (currentLayout + NumLayouts - 1)%NumLayouts;
         break;
      case GLUT_KEY_HOME:
         /* If the current layout is simple decrement its line length */
         if (simpleLayout) simpleLayout->SetLineLength(simpleLayout->GetLineLength() - 10.0f);
         break;
      case GLUT_KEY_END:
         /* If the current layout is simple increment its line length */
         if (simpleLayout) simpleLayout->SetLineLength(simpleLayout->GetLineLength() + 10.0f);
         break;
		case GLUT_KEY_LEFT:
         fonts[current_font]->FaceSize(fonts[current_font]->FaceSize() - 1);
			break;   
      case GLUT_KEY_RIGHT:
         fonts[current_font]->FaceSize(fonts[current_font]->FaceSize() + 1);
         break;
	}

	if (simpleLayout) { 
      simpleLayout->SetFont(fonts[current_font]);
   } /* If the current layout is a simple layout update it's font (if simpleLayout) */

	glutPostRedisplay();
}


void motion(int x, int y)
{
	tbMotion( x, y);
}

void mouse(int button, int state, int x, int y)
{
	tbMouse( button, state, x, y);
}

void myReshape(int w, int h)
{
	glMatrixMode (GL_MODELVIEW);
	glViewport (0, 0, w, h);
	glLoadIdentity();
		
	w_win = w;
	h_win = h;
	SetCamera();
	
	tbReshape(w_win, h_win);
}

void SetCamera(void)
{
	switch( current_font)
	{
		case FTGL_BITMAP:
		case FTGL_PIXMAP:
			glMatrixMode( GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(0, w_win, 0, h_win);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			break;
		case FTGL_OUTLINE:
		case FTGL_POLYGON:
		case FTGL_EXTRUDE:
		case FTGL_TEXTURE:
			glMatrixMode (GL_PROJECTION);
			glLoadIdentity ();
			gluPerspective( 90, (float)w_win / (float)h_win, 1, 1000);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt( 0.0, 0.0, (float)h_win / 2.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			break;
	}	
}


int main(int argc, char *argv[])
{
#ifndef __APPLE_CC__ // Bloody finder args???
	if (argc == 2)
		fontfile = argv[1];
#endif

	if (!fontfile)
	{
		fprintf(stderr, "A font file must be specified on the command line\n");
		exit(1);
	}

	glutInit( &argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize( w_win, h_win);
	glutCreateWindow("FTGL TEST");
	glutDisplayFunc(display);
	glutKeyboardFunc(parsekey);
   glutSpecialFunc(parseSpecialKey);
	glutMouseFunc(mouse);
    glutMotionFunc(motion);
	glutReshapeFunc(myReshape);
	glutIdleFunc(display);

	myinit( fontfile);

	glutMainLoop();

	return 0;
}
