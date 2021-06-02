#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
int n;
float v[4][3] = {
                 {0, 0, 1},
                 {0, 1, -1},
                 {-1, -1, -1},
                 {1, -1, -1}
                };

void triangle(float a[3], float b[3], float c[3]){
    glBegin(GL_TRIANGLES);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}

void d_triangle(float a[3], float b[3], float c[3], int m){
    int i;
    float v1[3], v2[3], v3[3];
    if(m > 0){
        for(i = 0; i < 3; i++){
            v1[i] = (a[i] + b[i])/2;
            v2[i] = (a[i] + c[i])/2;
            v3[i] = (b[i] + c[i])/2;
        }
        d_triangle(a, v1, v2, m - 1);
        d_triangle(b, v1, v3, m - 1);
        d_triangle(c, v3, v2, m - 1);
    }
    else{
        triangle(a, b, c);
    }
}


void tetra(int m){
    glColor3f(1, 0, 0);
    d_triangle(v[0], v[1], v[3], m);
    glColor3f(0, 1, 0);
    d_triangle(v[0], v[2], v[3], m);
    glColor3f(1, 1, 0);
    d_triangle(v[1], v[2], v[3], m);
    glColor3f(0, 0, 1);
    d_triangle(v[0], v[1], v[2], m);
}

void disp(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    tetra(n);
    glFlush();
}

void init(){
    glMatrixMode(GL_PROJECTION);
    glOrtho(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    printf("Enter number of divisions: ");
    scanf("%d", &n);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D Gasket");
    glutDisplayFunc(disp);
    init();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
