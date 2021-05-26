/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>


void display()
{
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0, 0, 1);
    glVertex2f(100, 200);
    glVertex2f(150, 275);
    glVertex2f(200, 200);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0, 0);
    glVertex2f(100, 100);
    glVertex2f(100, 200);
    glVertex2f(200, 200);
    glVertex2f(200, 100);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 1, 0);
    glVertex2f(125, 100);
    glVertex2f(125, 150);
    glVertex2f(175, 150);
    glVertex2f(175, 100);
    glEnd();
    glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0,500,0,500);

    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("simple");

    glutDisplayFunc(display);

    init();

    glutMainLoop();
}
