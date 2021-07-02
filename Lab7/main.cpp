#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

float v[8][3] = {{-1,-1,-1},{-1,1,-1},{1,1,-1},{1,-1,-1},{-1,-1,1},{-1,1,1},{1,1,1},{1,-1,1}};
static float theta[3] = {0,0,0};
float vi[3] = {0,0,5};

int axis = 1;


void cube(int a, int b, int c, int d){
    glBegin(GL_POLYGON);
        glVertex3fv(v[a]);
        glVertex3fv(v[b]);
        glVertex3fv(v[c]);
        glVertex3fv(v[d]);
    glEnd();
}


void polygon(){

    glColor3f(1,0,0);
    cube(4,5,1,0);
    glColor3f(0,1,0);
    cube(7,6,2,3);
    glColor3f(0,0,1);
    cube(6,5,1,2);
    glColor3f(1,1,0);
    cube(7,4,0,3);
    glColor3f(1,0,1);
    cube(0,1,2,3);
    glColor3f(0,1,1);
    cube(4,5,6,7);

}




void display(){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(vi[0],vi[1],vi[2],0,0,0,0,1,0);
    glRotatef(theta[0],1,0,0);
    glRotatef(theta[1],0,1,0);
    glRotatef(theta[2],0,0,1);
    polygon();
    glFlush();

    glutSwapBuffers();
}


void init(){
    glMatrixMode(GL_PROJECTION);
    glFrustum(-2,2,-2,2,2,10);
    glMatrixMode(GL_MODELVIEW);
}

void spinCube(){
    theta[axis]-=1;
    if(theta[axis] > 360)
        theta[axis] = 0;
    display();
}

void keys(unsigned char k, int x, int y){
    if(k == 'x')
        vi[0] = vi[0] - 1;
    if(k == 'X')
        vi[0] = vi[0] + 1;
    if(k == 'y')
        vi[1] = vi[1] - 1;
    if(k == 'Y')
        vi[1] = vi[1] + 1;
    if(k == 'z')
        vi[2] = vi[2] - 1;
    if(k == 'Z')
        vi[2] = vi[2] + 1;

    display();
}

void mouse(int button, int state, int x, int y){
    y = 500 - y;
    printf("%d %d\n", x, y);
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        axis = 0;
    if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        axis = 1;
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        axis = 2;

    spinCube();
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cube Rotation");
    glutDisplayFunc(display);
	init();
	glutKeyboardFunc(keys);
	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
