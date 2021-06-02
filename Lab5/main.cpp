#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

float x1, x2, x3, x4, y1, y2, y3, y4;
float le[500], re[500];
int flag = 0;

void edge(float x1, float y1, float x2, float y2){
    float m, x;
    int i, j;

/*
    if(y2 < y1){
        float temp;
        temp = y1;
        y1 = y2;
        y2 = temp;

        temp = x1;
        x1 = x2;
        x2 = temp;
    }
*/

    m = (y2 - y1) / (x2 - x1);
    x = x1;
    for(i = y1; i < y2; i++){
        if(x < le[i])
            le[i] = x;
        if(x > re[i])
            re[i] = x;
        x += 1 / m;
    }
}

void scanFill(float x1, float x2, float x3, float x4, float y1, float y2, float y3, float y4){
    int i, j;
    for(i = 0; i < 500; i++){
        le[i] = 500;
        re[i] = 0;
    }
    edge(x1, y1, x2, y2);
    edge(x2, y2, x3, y3);
    edge(x4, y4, x3, y3);
    edge(x1, y1, x4, y4);
    for(i = 0; i < 500; i++){
        for(j = le[i] - 1; j <= re[i]; j++){
            glColor3f(0, 0, 1);
            glBegin(GL_POINTS);
                glVertex2f(j, i);
            glEnd();
        }
    }
}


void display(){
    printf("Rendering window...\n");
    x1 = 200.0; y1 = 200.0;
    x2 = 100.0; y2 = 300.0;
    x3 = 200.0; y3 = 400.0;
    x4 = 300.0; y4 = 300.0;
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glVertex2f(x4, y4);
    glEnd();

    if(flag == 1)
        scanFill(x1, x2, x3, x4, y1, y2, y3, y4);
    glFlush();
}

void scanMenu(int id){
    switch(id){
    case 1:
        flag = 1;
        break;
    case 2:
        flag = 0;
        break;
    case 3:
        exit(0);
    }
    display();
}

void init(){
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Scan Line Algorithms");
    glutDisplayFunc(display);
	init();
	glutCreateMenu(scanMenu);
	glutAddMenuEntry("Fill the polygon", 1);
	glutAddMenuEntry("Outline", 2);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
