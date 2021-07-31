#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>

int id = 0, flag = 0;
float theta = 0;
int fact(int number){
    int i, z = 1;
    for(i = number; i > 1; i--){
        z *= i;
    }
    return z;
}

void combination(int n, float c[4]){
    int i;
    for(i = 0; i <= n; i++){
        c[i] = fact(n) / (fact(i) * fact(n - i));
    }
}

void curve(float cp[4][2]){
    float t, x, y, c[4];
    int i, n = 3;
    combination(n, c);
    glBegin(GL_LINE_STRIP);
    for(t = 0; t < 1; t += 0.05){
        x = 0, y = 0;
        for(i = 0; i <= 3; i++){
            x += cp[i][0] * pow(t, i) * pow(1-t, n-i) * c[i];
            y += cp[i][1] * pow(t, i) * pow(1-t, n-i) * c[i];
        }
        glVertex2f(x, y);
    }
    glEnd();
}

void display(){
    float cp[4][2] = {{20, 100}, {30, 110}, {40, 90}, {50, 100}};
    int i;
    glClearColor(1, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);


    if(flag == 1){
        cp[1][0] += sin(theta * 3.14 / 180);
        cp[1][1] += sin(theta * 3.14 / 180);
        cp[2][0] -= sin(theta * 3.14 / 180);
        cp[2][1] -= sin(theta * 3.14 / 180);
        cp[3][0] -= sin(theta * 3.14 / 180);
        cp[3][1] += sin(theta * 3.14 / 180);
        theta += 0.5;
    }



    if(id == 1){
        glPushMatrix();
        glLineWidth(3.0);

        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(20, 100);
        glVertex2f(20, 20);
        glEnd();
        glLineWidth(4.0);
        for(i = 0; i < 10; i++){
            glColor3f(1, 0.5, 0);
            glTranslatef(0, -1, 0);
            curve(cp);
        }
        for(i = 0; i < 10; i++){
            glColor3f(1, 1, 1);
            glTranslatef(0, -1, 0);
            curve(cp);
        }
        for(i = 0; i < 10; i++){
            glColor3f(0, 1, 0);
            glTranslatef(0, -1, 0);
            curve(cp);
        }
        glPopMatrix();
    }
    glutPostRedisplay();
    glutSwapBuffers();
    glFlush();
}

void menu(int num){
    if(num == 1){
        id = 1;
    }

    if(num ==2){
        flag = 1;
    }

    if(num == 3){
        flag = 0;
    }

    display();
}

void init(){
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 200, 0, 200);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Curve");
    init();
    glutCreateMenu(menu);
    	glutAddMenuEntry("Flag", 1);
    	glutAddMenuEntry("Start Animation", 2);
    	glutAddMenuEntry("Stop Animation", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
