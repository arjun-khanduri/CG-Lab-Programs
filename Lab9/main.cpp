#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

void tableLeg(){
    glPushMatrix();
    glScaled(0.02,0.3,0.02);
    glutSolidCube(1.0);
    glPopMatrix();
}

void wall(float thickness){
    glPushMatrix();
    glTranslatef(0.5,0,0.5);
    glScaled(1.0, thickness, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();
}

void init(){
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1, 1, -1, 1, 1, 4);
    glMatrixMode(GL_MODELVIEW);
}

void table(){
    glPushMatrix();
    glTranslatef(0,0.2,0);
    glScalef(0.8,0.05,0.8);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3,0,0.3);
    tableLeg();
    glTranslatef(0,0,-2*0.3);
    tableLeg();
    glTranslatef(-2*0.3,0,0);
    tableLeg();
    glTranslatef(0,0,2*0.3);
    tableLeg();
    glPopMatrix();
}

void display(){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    float lightIntensity[] = {1,0,0,1};
    float lightPosition[] = {2,4,3,1};
    float mat_amb[] = {1,0,1,1};
    glMaterialfv(GL_FRONT,GL_AMBIENT, mat_amb);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0,GL_INTENSITY, lightIntensity);
    glLoadIdentity();
    gluLookAt(2,2,2,0,0,0,0,1,0);

    glPushMatrix();
    glTranslatef(0.5,0.2,0.5);
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5,0.8,0.6);
    glutSolidTeapot(0.05);
    glPopMatrix();

    glPushMatrix();
        wall(0.05);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90,0,0,1);
        wall(0.05);
    glPopMatrix();

    glPushMatrix();
        glRotatef(-90,1,0,0);
        wall(0.05);
    glPopMatrix();

    glFlush();
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("");
    init();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
