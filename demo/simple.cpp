/*
 * simple.cpp - simple demo for FTGL, the OpenGL font library
 *
 * Copyright (c) 2008 Sam Hocevar <sam@zoy.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "config.h"

#include <math.h>

#if defined HAVE_GL_GLUT_H
#   include <GL/glut.h>
#elif defined HAVE_GLUT_GLUT_H
#   include <GLUT/glut.h>
#else
#   error GLUT headers not present
#endif

#include <FTGL/ftgl.h>

static FTFont *font;

static void RenderScene(void)
{
    float n = (float)glutGet(GLUT_ELAPSED_TIME) / 10.;
    float t1 = sin(n / 80);
    float t2 = sin(n / 50 + 1);
    float t3 = sin(n / 30 + 2);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
        glTranslatef(-0.9, -0.2, -10.0);
        float ambient[4]  = { (t1 + 2.0) / 3,
                                     (t2 + 2.0) / 3,
                                     (t3 + 2.0) / 3, 1.0 };
        float diffuse[4]  = { 1.0, 0.9, 0.9, 1.0 };
        float specular[4] = { 1.0, 0.7, 0.7, 1.0 };
        float position[4] = { 200.0, 200.0, 0.0, 1.0 };
        glLightfv(GL_LIGHT1, GL_AMBIENT,  ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE,  diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT1, GL_POSITION, position);
        glEnable(GL_LIGHT1);
        glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 0.0, 20.0);
        glRotatef(n / 1.11, 0.0, 1.0, 0.0);
        glRotatef(n / 2.23, 1.0, 0.0, 0.0);
        glRotatef(n / 3.17, 0.0, 0.0, 1.0);
        glTranslatef(-260.0, -0.2, 0.0);
        glColor3f(0.0, 0.0, 0.0);
        font->Render("Hello FTGL!");
    glPopMatrix();

    glutSwapBuffers();
}

void ProcessKeys(unsigned char key, int x, int y)
{
    if(key == 27)
    {
        delete font;
        exit(0);
    }
}

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s <font_name.ttf>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Initialise GLUT stuff
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("FTGL simple demo");

    glutDisplayFunc(RenderScene);
    glutIdleFunc(RenderScene);
    glutKeyboardFunc(ProcessKeys);

    // Initialise FTGL stuff
    font = new FTExtrudeFont(argv[1]);
    if(font->Error())
    {
        fprintf(stderr, "%s: could not load font `%s'\n", argv[0], argv[1]);
        return EXIT_FAILURE;
    }

    font->FaceSize(80);
    font->Depth(10);
    font->Outset(0, 3);
    font->CharMap(ft_encoding_unicode);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(90, 640.0f / 480.0f, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 640.0f / 2.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Run GLUT loop
    glutMainLoop();

    return EXIT_SUCCESS;
}

